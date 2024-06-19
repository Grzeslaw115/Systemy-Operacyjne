#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_cond_t santa_cond;
pthread_mutex_t santa_mutex;
int christmas_count = 0;
int reindeer_count = 0;
int finished = 0;

void *reindeer(void *id) {
    int reindeer_id = *(int*)id;
    while (!finished) {
        sleep(rand() % 6 + 5);

        pthread_mutex_lock(&santa_mutex);
        if (finished) {
            pthread_mutex_unlock(&santa_mutex);
            break;
        }
        reindeer_count++;
        printf("Renifer %d: czeka %d reniferow na Mikolaja\n", reindeer_id, 9 - reindeer_count);
        if (reindeer_count == 9) {
            printf("Renifer %d: wybudzam Mikolaja\n", reindeer_id);
            pthread_cond_signal(&santa_cond);
        }
        pthread_mutex_unlock(&santa_mutex);

        sleep(rand() % 5 + 2);
    }
    return NULL;
}

void *santa(void *arg) {
    while (christmas_count < 4) {
        pthread_mutex_lock(&santa_mutex);
        while (reindeer_count < 9 && !finished) {
            pthread_cond_wait(&santa_cond, &santa_mutex);
        }
        printf("Mikolaj: budze sie\n");
        printf("Mikolaj: dostarczam zabawki\n");
        sleep(rand() % 5 + 2);
        reindeer_count = 0;
        christmas_count++;
        printf("Mikolaj: zasypiam\n");
        pthread_mutex_unlock(&santa_mutex);
    }
    finished = 1;
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_cond_init(&santa_cond, NULL);
    pthread_mutex_init(&santa_mutex, NULL);

    pthread_t santa_thread;
    pthread_t reindeer_threads[9];
    int reindeer_ids[9];

    if(pthread_create(&santa_thread, NULL, santa, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    for (int i = 0; i < 9; i++) {
        reindeer_ids[i] = i + 1;
        if(pthread_create(&reindeer_threads[i], NULL, reindeer, (void*)&reindeer_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    pthread_join(santa_thread, NULL);
    for (int i = 0; i < 9; i++) {
        pthread_join(reindeer_threads[i], NULL);
    }

    pthread_cond_destroy(&santa_cond);
    pthread_mutex_destroy(&santa_mutex);

    return 0;
}