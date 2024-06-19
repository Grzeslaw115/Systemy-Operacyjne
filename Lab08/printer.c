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
    Queue* queue;
    int printer_id;
    sem_t* sem_queue;
} ThreadArg;

void handle_sigint(int sig) {
    keep_running = 0;
}

Queue* init_queue() {
    int fd = shm_open("/print_queue", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("shm_open");
        return NULL;
    }

    if (ftruncate(fd, sizeof(Queue)) == -1) {
        perror("ftruncate");
        close(fd);
        return NULL;
    }

    Queue* queue = mmap(NULL, sizeof(Queue), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (queue == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return NULL;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    close(fd);
    return queue;
}

void* printer_thread(void* arg) {
    ThreadArg* thread_arg = (ThreadArg*)arg;
    Queue* queue = thread_arg->queue;
    int printer_id = thread_arg->printer_id;

    // Otwieranie jednego wspólnego semafora do kolejki
    sem_t* sem_queue = sem_open("/sem_queue", O_CREAT, 0666, 1);
    if (sem_queue == SEM_FAILED) {
        perror("sem_open for queue");
        exit(EXIT_FAILURE);
    }

    while (keep_running) {
        sem_wait(sem_queue); 

        if (queue->size > 0) {
            char print_data[11];
            strncpy(print_data, queue->queue[queue->head], 10);
            print_data[10] = '\0';
            queue->head = (queue->head + 1) % QUEUE_SIZE;
            queue->size--;

            sem_post(sem_queue);

            // Proces drukowania
            for (int i = 0; i < 10; i++) {
                printf("\nPrinter %d printing: ", printer_id);
                printf("%c", print_data[i]);
                fflush(stdout);
                printf("\n");
                sleep(1);
            }
            printf("\n");
        } else {
            sem_post(sem_queue);
        }

        sleep(1);
    }

    sem_close(sem_queue);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    signal(SIGINT, handle_sigint); 

    Queue* queue = init_queue(); 
    if (queue == NULL) {
        return 1;
    }

    int number_of_printers = (argc == 1) ? 1 : atoi(argv[1]);

    if (number_of_printers < 1) {
        perror("Error: Wrong number of printers.");
        return 1;
    }

    pthread_t printer_threads[number_of_printers];
    ThreadArg thread_args[number_of_printers];

    for (int i = 0; i < number_of_printers; i++) {
        thread_args[i].queue = queue;
        thread_args[i].printer_id = i;
        pthread_create(&printer_threads[i], NULL, printer_thread, (void*)&thread_args[i]);
    }

    for (int i = 0; i < number_of_printers; i++) {
        pthread_join(printer_threads[i], NULL);
    }

    if (keep_running == 0) {
        printf("Exiting...\n");
        // Clean up
        munmap(queue, sizeof(Queue));
        shm_unlink("/print_queue");
    }
    return 0;
}