#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int modeChangeRequests = 0;
int mode = 1;

void handler(int sig, siginfo_t *info, void *ucontext) {
    mode = info->si_value.sival_int;
    pid_t sender_pid = info->si_pid;
    
    if (mode == 1) {
        for (int i = 1; i <= 100; i++) {
            printf("%d\n", i);
        }
    } else if (mode == 2) {
        modeChangeRequests++;
        printf("Ilosc zadan zmiany trybu: %d\n", modeChangeRequests);
    } else if (mode == 3) {
        exit(0);
    }

    union sigval value;
    sigqueue(sender_pid, SIGUSR1, value);
}

int main() {
    printf("Catcher PID: %d\n", getpid());

    struct sigaction act;
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &act, NULL);

    while (1) {
        pause();
    }
}