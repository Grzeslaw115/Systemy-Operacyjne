#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 5
#define INIT 1
#define CLIENT 2

struct message {
    long type;
    char text[100];
};

int clients_queue[MAX_CLIENTS];
int clients_count = 0;

int init_server() {
    key_t key = ftok("./server_key_file", 'S');
    int queue_id = msgget(key, IPC_CREAT | 0666);
    if (queue_id == -1) {
        perror("queue_id");
        exit(-1);
    }
    printf("Serwer uruchomiony\n");
    return queue_id;
}

void process_messages(int queue_id) {
    while (1) {
        struct message msg;
        if (msgrcv(queue_id, &msg, sizeof(msg.text), 0, 0) == -1) {
            perror("msgrcv");
            continue;
        }

        if (msg.type == INIT) {
            if (clients_count >= MAX_CLIENTS) {
                printf("Osiagnieto maksymalna liczbe klientow!\n");
                continue;
            }

            int client_queue_id = atoi(msg.text);
            clients_queue[clients_count] = client_queue_id;
            clients_count++;

            struct message response;
            response.type = INIT;
            snprintf(response.text, sizeof(response.text), "%d", clients_count);

            if (msgsnd(client_queue_id, &response, sizeof(response.text), 0) == -1) {
                perror("msgsnd");
            } else {
                printf("Do serwera dolaczyl klient %d\n", clients_count);
            }
        } else if (msg.type == CLIENT) {
            printf("Wyslano wiadomosc: %s\n", msg.text);

            for (int i = 0; i < clients_count; i++) {
                if (msgsnd(clients_queue[i], &msg, sizeof(msg.text), 0) == -1) {
                    perror("msgsnd");
                }
            }
        }
    }
}

int main() {
    int queue_id = init_server();
    process_messages(queue_id);
    return 0;
}