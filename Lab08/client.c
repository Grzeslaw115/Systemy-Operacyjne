#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>

#define QUEUE_SIZE 10

char keep_running = 1;

typedef struct {
    char queue[QUEUE_SIZE][11];
    int head;                   
    int tail;                   
    int size;                  
} Queue;

typedef struct {
    Queue *queue;
    int client_id;
} ThreadArg;

void handle_sigint(int sig) {
    keep_running = 0;
}

void generate_random_string(char* str, int len) {
    for (int i = 0; i < len; i++) {
        str[i] = 'a' + rand() % 26;
    }
    str[len] = '\0';
}

void* user_thread(void* arg) {
    ThreadArg* thread_arg = (ThreadArg*)arg;
    Queue* queue = thread_arg->queue;
    int client_id = thread_arg->client_id;
    sem_t *sem_queue = sem_open("/sem_queue", 0);

    while(keep_running) {
        sem_wait(sem_queue); // Wait for access to the queue
        if (queue->size < QUEUE_SIZE) {
            char str[11];
            generate_random_string(str, 10);
            strcpy(queue->queue[queue->tail], str);
            queue->tail = (queue->tail + 1) % QUEUE_SIZE;
            queue->size++;
            printf("Client %d added string %s\n", client_id, str); fflush(stdout);
            sem_post(sem_queue);
            sleep(rand() % 5 + 1); // Sleep for 1-5 seconds
        } else {
            sem_post(sem_queue);
            sleep(1);
        }
    }
    return NULL;
}

int main(int argc, char** argv) {
    signal(SIGINT, handle_sigint);
    srand(time(NULL) + getpid());

    int fd = shm_open("/print_queue", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    ftruncate(fd, sizeof(Queue));
    Queue* queue = mmap(NULL, sizeof(Queue), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (queue == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    sem_t *sem_queue = sem_open("/sem_queue", O_CREAT, 0666, 1);
    if (sem_queue == SEM_FAILED) {
        perror("sem_open");
        munmap(queue, sizeof(Queue));
        close(fd);
        return 1;
    }

    int number_of_clients = (argc == 1) ? 1 : atoi(argv[1]);

    if (number_of_clients < 1) {
        printf("Error: Wrong number of clients.\n");
        return 1;
    }

    pthread_t threads[number_of_clients];
    ThreadArg thread_args[number_of_clients];

    for (int i = 0; i < number_of_clients; i++) {
        thread_args[i].queue = queue;
        thread_args[i].client_id = i;
        pthread_create(&threads[i], NULL, user_thread, (void*)&thread_args[i]);
    }

    for (int i = 0; i < number_of_clients; i++) {
        pthread_join(threads[i], NULL);
    }

    if (keep_running == 0) {
        printf("Exiting... \n");
        shm_unlink("print_queue");
        sem_close(sem_queue);
    }
    return 0;
}