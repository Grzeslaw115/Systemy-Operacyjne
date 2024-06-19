#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

double calculateIntegralPart(double a, double b, double h) {
    double result = 0;
    for (double i = a; i < b; i += h) {
        double x = i + h / 2; // Srodek prostokata
        result += h * 4 / (x * x + 1);
    }
    return result;
}

double calculateIntegral(double h, int n) {

    int fds[n][2];
    double result = 0;

    for (int i = 0; i < n; i++) {
        if (pipe(fds[i]) == -1) {
            printf("Blad podczas tworzenia potoku\n");
            return -1;
        }

        pid_t pid = fork();
        if (pid == 0) { // Proces potomny
            close(fds[i][0]);
            double a = 1.0 / n * i;
            double b = 1.0 / n * (i + 1);

            double localResult = calculateIntegralPart(a, b, h);
            write(fds[i][1], &localResult, sizeof(localResult));
            close(fds[i][1]);
            exit(0);
        } else if (pid > 0) { // Proces rodzica
            close(fds[i][1]);
        }
    }

    // Sumowanie wynikow
    for (int i = 0; i < n; i++) {
        double localResult;
 
        read(fds[i][0], &localResult, sizeof(localResult));
        result += localResult;
        close(fds[i][0]);
    }

    return result;
}

void measureAndLogResults() {
    double hValues[] = {0.0000001, 0.000000001};
    int nValues[] = {1, 10, 100};
    int hSize = sizeof(hValues) / sizeof(hValues[0]);
    int nSize = sizeof(nValues) / sizeof(nValues[0]);

    FILE *file = fopen("raport_czasowy.txt", "w");
    if (file == NULL) {
        printf("Błąd przy otwieraniu pliku raportu.\n");
        return;
    }

    for (int i = 0; i < hSize; i++) {
        for (int j = 0; j < nSize; j++) {
            clock_t start = clock();
            calculateIntegral(hValues[i], nValues[j]);
            clock_t end = clock();
            double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;

            fprintf(file, "h: %f, Liczba procesów: %d, Czas: %f sekund\n", hValues[i], nValues[j], timeSpent);
            fflush(file);
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        measureAndLogResults();
    } else if (argc == 3) {
        double h = atof(argv[1]);
        if (h <= 0) {
            printf("Nieprawidlowa wartosc h\n");
            return -1;
        }

        int n = atoi(argv[2]);
        if (n <= 0) {
            printf("Nieprawidlowa liczba procesow\n");
            return -1;
        }

        double result = calculateIntegral(h, n);
        printf("Wynik: %f\n", result);
    } else {
        printf("Niepoprawna liczba argumentow.\n");
        return -1;
    }
    return 0;
}