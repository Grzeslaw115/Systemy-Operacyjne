#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int global = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Nieprawidlowa liczba argumentow.\n");
        return 1;
    }

    int local = 0;
    pid_t pid;

    printf("%s\n", argv[0]);

    pid = fork();

    if (pid < 0) {
        printf("Nie udalo sie utworzyc procesu potomnego.\n");
        return 2;
    }

    if (pid == 0) { // Proces potomny
        printf("child process\n");
        global++;
        local++;
        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
        printf("child's local = %d, child's global = %d\n", local, global);

        int status = execl("/bin/ls", "ls", argv[1], (char *)NULL);
        exit(status);
    } else { // Proces rodzica
        int status;
        wait(&status);
        printf("parent process\n");
        printf("parent pid = %d, child pid = %d\n", getpid(), pid);
        printf("Child exit code: %d\n", WEXITSTATUS(status));
        printf("parent's local = %d, parent's global = %d\n", local, global);
        exit(WEXITSTATUS(status));
    }
}