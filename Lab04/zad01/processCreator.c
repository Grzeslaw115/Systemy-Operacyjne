#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Nieprawidlowa liczba argumentow\n");
        return 1;
    }

    if(atoi(argv[1]) < 1) {
        printf("Liczba procesow musi byc wieksza od 0\n");
        return 1;
    }

    pid_t pid;

    for(int i = 0; i < atoi(argv[1]); i++) {
        pid = fork();

        if (pid < 0) {
            printf("Nie udalo sie utworzyc procesu.\n");
            return 2;
        }

        if (pid == 0) { //proces potomny
            printf("Identyfikator procesu macierzystego: %d, wlasny identyfikator: %d\n", getppid(), getpid());
            return 0;
        }
    }

    while(wait(NULL) > 0);
    printf("%d\n", atoi(argv[1]));
    return 0;
}