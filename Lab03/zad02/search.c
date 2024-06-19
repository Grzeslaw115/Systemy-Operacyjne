#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent* file;
    struct stat bufor_stat;
    long long size_all = 0;

    if (dir == NULL) {
        printf("Nie udalo sie otworzyc katalogu.");
        return 1;
    }

    while ((file = readdir(dir)) != NULL) {

        // Sprawdzanie, czy udalo sie pobrac informacje o pliku.
        if (stat(file->d_name, &bufor_stat) == -1) {
            printf("Nie udalo sie pobrac informacji o pliku: %s\n", file->d_name);
            continue;
        }

        // Sprawdzanie, czy to nie jest katalog
        if (!S_ISDIR(bufor_stat.st_mode)) {
            printf("Plik o nazwie: %s, ma rozmiar: %lld bajtów.\n", file->d_name, (long long)bufor_stat.st_size);
            size_all += bufor_stat.st_size;
        }
    }

    printf("Rozmiar wszystkich plikow w katalogu: %lld bajtów.\n", size_all);

    closedir(dir);
    return 0;
}