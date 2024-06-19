#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT 1
#define CLIENT 2

struct message {
    long type;
    char text[100];
};

int create_client_queue() {
    key_t key = ftok("./client_key_file", 'C');
    int queue_id = msgget(key, IPC_CREAT | 0666);
    if (queue_id == -1) {
        perror("queue_id");
        exit(-1);
    }
    return queue_id;
}

int connect_to_server(int server_queue_id, int client_queue_id) {
    struct message msg;
    msg.type = INIT;
    snprintf(msg.text, sizeof(msg.text), "%d", client_queue_id);
    if (msgsnd(server_queue_id, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd");
        exit(-1);
    }

    if (msgrcv(client_queue_id, &msg, sizeof(msg.text), INIT, 0) == -1) {
        perror("msgrcv");
        exit(-1);
    }

    int client_id = atoi(msg.text);
    printf("Polaczono z serwerem, ID: %d\n", client_id);

    return client_id;
}

void send_message(int server_queue_id, int client_id) {
    while (1) {
        struct message msg;
        msg.type = CLIENT;
        fgets(msg.text, sizeof(msg.text), stdin);

        // Dodaj ID klienta do wiadomosci
        char with_client_id[128];
        sprintf(with_client_id, "Klient %d: %s", client_id, msg.text);
        strncpy(msg.text, with_client_id, sizeof(msg.text));

        if (msgsnd(server_queue_id, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd");
            exit(-1);
        }
        printf("Wyslano wiadomosc\n");
    }
}

void receive_messages(int client_queue_id) {
    while (1) {
        struct message msg;
        if (msgrcv(client_queue_id, &msg, sizeof(msg.text), CLIENT, 0) == -1) {
            perror("msgrcv");
            continue;
        }
        printf("%s", msg.text);
    }
}

int main() {
    int client_queue_id = create_client_queue();

    key_t server_key = ftok("./server_key_file", 'S');
    int server_queue_id = msgget(server_key, 0);
    if (server_queue_id == -1) {
        perror("server_queue_id");
        exit(-1);
    }
    int client_id = connect_to_server(server_queue_id, client_queue_id);

    pid_t pid = fork();

    if (pid == 0) {
        receive_messages(client_queue_id);
    } else {
        send_message(server_queue_id, client_id);
    }

    return 0;
}