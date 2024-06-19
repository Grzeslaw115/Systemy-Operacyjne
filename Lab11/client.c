#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 256

char client_id[20];
int socket_fd;
int keep_running = 1;

void signal_handler(int signum) {
    keep_running = 0;
    write(socket_fd, "STOP", 4);
    close(socket_fd);
    printf("Client disconnected\n");
}


void* receive_messages() {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(socket_fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        // If its ALIVE message, ignore it
        if (strcmp(buffer, "ALIVE") == 0) {
            continue;
        }
        printf("Serwer wyslal wiadomosc: %s\n", buffer);
    }

    if (bytes_read == 0) { // 0 means server closed connection
        printf("Serwer zamknął połączenie\n");
    } else if (bytes_read == -1) {
        perror("Read error");
    }

    close(socket_fd);
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);

    if (argc != 4) {
        perror("Wrong number of arguments\n");
        return -1;
    }

    strncpy(client_id, argv[1], sizeof(client_id) - 1);
    client_id[sizeof(client_id) - 1] = '\0';
    char *server_address = argv[2];
    int server_port = atoi(argv[3]);

    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("Socket error");
        return -1;
    }

    // Connect
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, server_address, &server_addr.sin_addr);

    if (connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("Connect error");
        close(socket_fd);
        return -1;
    }

    // Send client ID
    if (write(socket_fd, client_id, strlen(client_id)) == -1) {
        perror("Sending ID error");
        close(socket_fd);
        return -1;
    }

    // Thread for receiving messages
    pthread_t receive_thread;
    if (pthread_create(&receive_thread, NULL, receive_messages, NULL) != 0) {
        perror("Thread create error");
        close(socket_fd);
        return -1;
    }

    // Send messages
    while (keep_running) {
        printf("Podaj komende: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            write(socket_fd, buffer, strlen(buffer));
        }
    }

    pthread_join(receive_thread, NULL);
    close(socket_fd);

    printf("Client program exited\n");
    return 0;
}