#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int confirmationReceived = 0;

void handler(int sig, siginfo_t *info, void *ucontext) {
    confirmationReceived = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Nieprawidlowa liczba argumentow\n");
        return -1;
    }

    pid_t catcher_pid = atoi(argv[1]);
    int mode = atoi(argv[2]);

    union sigval value;
    value.sival_int = mode;

    struct sigaction act;
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);

    sigqueue(catcher_pid, SIGUSR1, value);

    while (!confirmationReceived) {
        pause();
    }

    printf("Otrzymano potwierdzenie.\n");

    return 0;
}