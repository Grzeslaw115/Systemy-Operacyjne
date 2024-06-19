#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#define GRID_SIZE 30

pthread_t *threads;
char keep_running = 1;
int n;

typedef struct {
	int start;
	int end;
	char *foreground;
	char *background;
} ThreadArgs;

void sigusr1_handler(int signo) {
    // Nic nie rób - używane tylko do wznowienia wątków
}

void resume_threads(int n, pthread_t *threads) {
    for (int i = 0; i < n; i++) {
        pthread_kill(threads[i], SIGUSR1);
    }
}

void sigint_handler(int signo) {
    if (signo == SIGINT) {
        keep_running = 0;
		resume_threads(n, threads);
    }
}

void *update_grid_thread(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    while (keep_running) {
        for (int i = args->start; i <= args->end; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                args->background[i * GRID_SIZE + j] = is_alive(i, j, args->foreground);
            }
        }
        pause(); // Czekaj na sygnał do wznowienia
    }
    return NULL;
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Wrong number of arguments\n");
		return -1;
	}

	n = atoi(argv[1]);
	if (n < 1) {
		printf("Invalid argument\n");
		return -1;
	}

	signal(SIGUSR1, sigusr1_handler);
    signal(SIGINT, sigint_handler);

	threads = malloc(n * sizeof(pthread_t)); // Allocate memory for threads
	if (threads == NULL) {
		printf("Memory allocation failed\n");
		return -1;
	}

	srand(time(NULL));
	setlocale(LC_CTYPE, "");
	initscr(); // Start curses mode

	char *foreground = create_grid();
	char *background = create_grid();
	char *tmp;

	init_grid(foreground);

	// Create threads
	ThreadArgs *args = malloc(n * sizeof(ThreadArgs));
	int chunk = GRID_SIZE / n;

	for (int i = 0; i < n; i++) {
		args[i].start = i * chunk;
		args[i].end = (i == n - 1) ? GRID_SIZE : (args[i].start + chunk - 1);
		args[i].foreground = foreground;
		args[i].background = background;

		if (pthread_create(&threads[i], NULL, update_grid_thread, &args[i]) != 0) {
		    perror("Failed to create thread");
		    return -1;
		}
	}

	while (true) {
		if (!keep_running) {
			break;
		}

		// Send signal to threads
		//resume_threads(n, threads);

		draw_grid(foreground);
		usleep(500 * 1000);

		tmp = foreground;
		foreground = background;
		background = tmp;
	}

	for (int i = 0; i < n; i++) {
    	pthread_join(threads[i], NULL);
	}

	// Clean up
	endwin(); // End curses mode
	destroy_grid(foreground);
	destroy_grid(background);
	free(threads);
	free(args);

	return 0;
}