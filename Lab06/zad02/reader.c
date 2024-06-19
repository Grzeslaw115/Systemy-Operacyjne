#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Niepoprawna liczba argumentow.\n");
        return -1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);

    if (mkfifo("namedPipe", 0777) == -1) {
        if (errno != EEXIST) { // Mozliwe ze potok juz istnieje
            printf("Blad podczas tworzenia potoku\n");
            return -1;
        } 
    }

    int fd = open("namedPipe", O_WRONLY);
    if (fd == -1) {
        printf("Blad podczas otwierania potoku\n");
        return -1;
    }

    write(fd, &a, sizeof(a));
    write(fd, &b, sizeof(b));
    close(fd);

    int fd2 = open("namedPipe", O_RDONLY);
    if (fd2 == -1) {
        printf("Blad podczas otwierania potoku\n");
        return -1;
    }

    double result;
    read(fd2, &result, sizeof(result));

    printf("Wynik: %f\n", result);

    return 0;
}