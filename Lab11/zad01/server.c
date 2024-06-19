#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 256

typedef struct {
    int socket;
    char id[20];
    int active;
    pthread_t thread;
} Client;

int server_socket;
Client clients[MAX_CLIENTS];
int keep_running = 1;

void *handle_client(void *arg);
void send_to_all(char *message, char *sender_id);
void send_to_one(char *message, char *sender_id, char *receiver_id);
void list_clients(int client_socket);
void *check_alive(void *arg);
void cleanup_client(int i);

void signal_handler(int signum) {
    keep_running = 0;
    close(server_socket);
    printf("Server closing...\n");
}

void *handle_client(void *arg) {
    Client *client = (Client *)arg;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(client->socket, buffer, sizeof(buffer) - 1)) > 0 && keep_running) {
        buffer[bytes_read] = '\0';

        if (strcmp(buffer, "LIST") == 0) {
            list_clients(client->socket);
        } else if (strncmp(buffer, "2ALL ", 5) == 0) {
            send_to_all(buffer + 5, client->id);
        } else if (strncmp(buffer, "2ONE ", 5) == 0) {
            char *target_id = strtok(buffer + 5, " ");
            char *message = strtok(NULL, "");
            if (target_id && message) {
                send_to_one(message, client->id, target_id);
            }
        } else if (strcmp(buffer, "STOP") == 0) {
            break;
        } else {
            write(client->socket, "Unknown command", 15);
        }
    }

    cleanup_client(client - clients);
    return NULL;
}

void send_to_all(char *message, char *sender_id) {
    char buffer[BUFFER_SIZE];
    time_t now = time(NULL);
    snprintf(buffer, sizeof(buffer), "Time: %s ID: %s Message: %s", ctime(&now), sender_id, message);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active && strcmp(clients[i].id, sender_id) != 0) {
            write(clients[i].socket, buffer, strlen(buffer));
        }
    }
}

void send_to_one(char *message, char *sender_id, char *receiver_id) {
    char buffer[BUFFER_SIZE];
    time_t now = time(NULL);
    snprintf(buffer, sizeof(buffer), "[%s] %s: %s", ctime(&now), sender_id, message);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active && strcmp(clients[i].id, receiver_id) == 0) {
            if (strcmp(clients[i].id, sender_id) == 0) {
                write(clients[i].socket, "You can't send message to yourself", 34);
                return;
            }
            write(clients[i].socket, buffer, strlen(buffer));
            return;
        }
    }

    // Receiver not found
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active && strcmp(clients[i].id, sender_id) == 0) {
            write(clients[i].socket, "Receiver not found", 18);
            break;
        }
    }
}

void list_clients(int client_socket) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active) {
            write(client_socket, clients[i].id, strlen(clients[i].id));
            write(client_socket, "\n", 1);
        }
    }
}

void *check_alive(void *arg) {
    while (keep_running) {
        sleep(25); 
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].active) {
                if (write(clients[i].socket, "ALIVE", 5) < 0) {
                    cleanup_client(i);
                }
            }
        }
    }
    return NULL;
}

void cleanup_client(int i) {
    close(clients[i].socket);
    clients[i].active = 0;
    printf("Client %s disconnected\n", clients[i].id);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments!\n");
        return -1;
    }

    signal(SIGINT, signal_handler);

    int client_socket, port;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    port = atoi(argv[1]);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket error");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind error");
        close(server_socket);
        return 1;
    }

    // Listen
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen error");
        close(server_socket);
        return 1;
    }

    printf("Server listening on port %d\n", port);

    // Start thread to ping clients
    pthread_t alive_thread;
    pthread_create(&alive_thread, NULL, check_alive, NULL);

    while (keep_running) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            if (keep_running) {
                perror("Accept error");
            }
            continue;
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (!clients[i].active) {
                clients[i].socket = client_socket;
                clients[i].active = 1;
                read(client_socket, clients[i].id, sizeof(clients[i].id) - 1); // Read client ID (sent by client)
                clients[i].id[sizeof(clients[i].id) - 1] = '\0';
                pthread_create(&clients[i].thread, NULL, handle_client, &clients[i]);
                break;
            }
        }
    }

    pthread_join(alive_thread, NULL);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active) {
            pthread_join(clients[i].thread, NULL);
        }
    }

    return 0;
}