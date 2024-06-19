#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void handler(int signum) {
    printf("Otrzymano sygnał SIGUSR1\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Nieprawidłowa liczba argumentów\n");
        return -1;
    }
 
    if (strcmp(argv[1], "ignore") == 0) {
        signal(SIGUSR1, SIG_IGN);
    } else if (strcmp(argv[1], "handler") == 0) {
        signal(SIGUSR1, handler);
    } else if (strcmp(argv[1], "mask") == 0) {
        sigset_t masked;
        sigemptyset(&masked);
        sigaddset(&masked, SIGUSR1);
        sigprocmask(SIG_BLOCK, &masked, NULL);
    } else if (strcmp(argv[1], "none") != 0) {
        printf("Nieprawidłowy argument\n");
        return -1;
    }

    raise(SIGUSR1);

    if (strcmp(argv[1], "mask") == 0) {
        sigset_t pending;
        sigpending(&pending);
        if (sigismember(&pending, SIGUSR1)) {
            printf("Sygnał SIGUSR1 oczekuje na odblokowanie\n");
        }
    }

    return 0;
}