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
    struct sockaddr_in addr;
    char id[20];
    int active;
} Client;

int server_socket;
Client clients[MAX_CLIENTS];
int keep_running = 1;
struct sockaddr_in server_addr;

void handle_client(struct sockaddr_in client_addr, char *message);
void send_to_all(char *message, char *sender_id);
void send_to_one(char *message, char *sender_id, char *receiver_id);
void list_clients(struct sockaddr_in client_addr);
void *check_alive(void *arg);
void cleanup_client(int index);

void signal_handler(int signum) {
    keep_running = 0;
    close(server_socket);
    printf("Server closing...\n");
}

void handle_client(struct sockaddr_in client_addr, char *message) {
    char buffer[BUFFER_SIZE];
    char client_id[20];
    int client_index = -1;

    // Find the client by address
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active && clients[i].addr.sin_addr.s_addr == client_addr.sin_addr.s_addr && clients[i].addr.sin_port == client_addr.sin_port) {
            client_index = i;
            strcpy(client_id, clients[i].id);
            break;
        }
    }

    // If client not found, register it
    if (client_index == -1) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (!clients[i].active) {
                clients[i].addr = client_addr;
                clients[i].active = 1;
                strncpy(clients[i].id, message, sizeof(clients[i].id) - 1);
                clients[i].id[sizeof(clients[i].id) - 1] = '\0';
                client_index = i;
                strcpy(client_id, clients[i].id);
                printf("Client %s connected\n", clients[i].id);
                return;
            }
        }
    }

    // Handle commands
    if (strcmp(message, "LIST") == 0) {
        list_clients(client_addr);
    } else if (strncmp(message, "2ALL ", 5) == 0) {
        send_to_all(message + 5, client_id);
    } else if (strncmp(message, "2ONE ", 5) == 0) {
        char *target_id = strtok(message + 5, " ");
        char *msg = strtok(NULL, "");
        if (target_id && msg) {
            send_to_one(msg, client_id, target_id);
        }
    } else if (strcmp(message, "STOP") == 0) {
        cleanup_client(client_index);
    } else {
        snprintf(buffer, sizeof(buffer), "Unknown command");
        sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    }
}

void send_to_all(char *message, char *sender_id) {
    char buffer[BUFFER_SIZE];
    time_t now = time(NULL);
    snprintf(buffer, sizeof(buffer), "Time: %s ID: %s Message: %s", ctime(&now), sender_id, message);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active && strcmp(clients[i].id, sender_id) != 0) {
            sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr));
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
                snprintf(buffer, sizeof(buffer), "You can't send message to yourself");
                sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr));
                return;
            }
            sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr));
            return;
        }
    }

    // Receiver not found
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active && strcmp(clients[i].id, sender_id) == 0) {
            snprintf(buffer, sizeof(buffer), "Receiver not found");
            sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr));
            break;
        }
    }
}

void list_clients(struct sockaddr_in client_addr) {
    char buffer[BUFFER_SIZE] = "";

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active) {
            strncat(buffer, clients[i].id, sizeof(buffer) - strlen(buffer) - 1);
            strncat(buffer, "\n", sizeof(buffer) - strlen(buffer) - 1);
        }
    }

    sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
}

void *check_alive(void *arg) {
    while (keep_running) {
        sleep(25);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].active) {
                if (sendto(server_socket, "ALIVE", 5, 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr)) < 0) {
                    cleanup_client(i);
                }
            }
        }
    }
    return NULL;
}

void cleanup_client(int index) {
    clients[index].active = 0;
    printf("Client %s disconnected\n", clients[index].id);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments!\n");
        return -1;
    }

    signal(SIGINT, signal_handler);

    int port;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    port = atoi(argv[1]);
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Server listening on port %d\n", port);

    // Start thread to ping clients
    pthread_t alive_thread;
    pthread_create(&alive_thread, NULL, check_alive, NULL);

    char buffer[BUFFER_SIZE];
    while (keep_running) {
        int bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_addr, &client_addr_len);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            handle_client(client_addr, buffer);
        }
    }

    pthread_join(alive_thread, NULL);

    return 0;
}