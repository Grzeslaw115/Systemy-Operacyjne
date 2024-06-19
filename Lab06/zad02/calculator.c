#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

double calculateIntegral(double a, double b, double h) {
    double result = 0;
    for (double i = a; i < b; i += h) {
        double x = i + h / 2; // Srodek prostokata
        result += h * 4 / (x * x + 1);
    }
    return result;
}

int main() {
    double a, b;
    int fd = open("namedPipe", O_RDONLY);
    if (fd == -1) {
        printf("Blad podczas otwierania potoku\n");
        return -1;
    }

    read(fd, &a, sizeof(a));
    read(fd, &b, sizeof(b));
    close(fd);

    double h = 0.0001; // Ustalona odgornie
    double result = calculateIntegral(a, b, h);

    int fd2 = open("namedPipe", O_WRONLY);
    if (fd2 == -1) {
        printf("Blad podczas otwierania potoku\n");
        return -1;
    }

    write(fd2, &result, sizeof(result));
    close(fd2);

    return 0;
}