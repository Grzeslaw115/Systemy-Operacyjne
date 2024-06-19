#include <stdio.h>

// Czytanie po jednym znaku.
void reverseByCharacter(const char *src, const char *dest) {
    FILE *srcFile = fopen(src, "rb");
    FILE *destFile = fopen(dest, "wb");

    if (srcFile == NULL || destFile == NULL) {
        printf("Nie udalo sie otworzyc plikow.");
        if (srcFile) fclose(srcFile);
        if (destFile) fclose(destFile);
        return;
    }

    fseek(srcFile, 0, SEEK_END);
    int steps = ftell(srcFile);

    if (steps == 0) {
        fclose(srcFile);
        fclose(destFile);
        return;
    }
    
    fseek(srcFile, -1, SEEK_END);
    for (int i = 0; i < steps; i++) {
        int c = fgetc(srcFile); //przesuwa o 1 bajt do przodu wiec trzeba sie pozniej cofnac o 2
        fputc(c, destFile);
        fseek(srcFile, -2, SEEK_CUR);
    }

    fclose(srcFile);
    fclose(destFile);
}

// Czytanie w bloku po 1024 znaki.
void reverseByBlock(const char *src, const char *dest) {
    FILE *srcFile = fopen(src, "rb");
    FILE *destFile = fopen(dest, "wb");

    if (srcFile == NULL || destFile == NULL) {
        printf("Nie udalo sie otworzyc plikow.\n");
        if (srcFile) fclose(srcFile);
        if (destFile) fclose(destFile);
        return;
    }

    const int blockSize = 1024;
    char buffer[blockSize];

    fseek(srcFile, 0, SEEK_END);

    int fileSize = ftell(srcFile);
    if (fileSize == 0) {
        fclose(srcFile);
        fclose(destFile);
        return;
    }

    int full_blocks = fileSize / blockSize;
    int last_block_size = fileSize % blockSize;

    // Obsluz ostatni, niepelny blok jesli istnieje
    if (last_block_size > 0) {
        fseek(srcFile, -last_block_size, SEEK_END);
        fread(buffer, sizeof(char), last_block_size, srcFile);

        // Odwracanie znakow w bloku
        for (int j = 0; j < last_block_size / 2; j++) {
            char temp = buffer[j];
            buffer[j] = buffer[last_block_size - j - 1];
            buffer[last_block_size - j - 1] = temp;
        }

        fwrite(buffer, sizeof(char), last_block_size, destFile);
    }

    // Obsłuż pełne bloki
    for (int i = 0; i < full_blocks; i++) {
        fseek(srcFile, -(blockSize * (i + 1) + last_block_size), SEEK_END);
        fread(buffer, sizeof(char), blockSize, srcFile);

        // Odwracanie znakow w bloku
        for (int j = 0; j < blockSize / 2; j++) {
            char temp = buffer[j];
            buffer[j] = buffer[blockSize - j - 1];
            buffer[blockSize - j - 1] = temp;
        }

        fwrite(buffer, sizeof(char), blockSize, destFile);
    }

    fclose(srcFile);
    fclose(destFile);
}

// Napisz program, który kopiuje zawartość jednego pliku do drugiego, odwróconą bajt po bajcie.
int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Niepoprawna liczba argumentow.\n");
        return 1;
    }

    #ifdef CHAR
    reverseByCharacter(argv[1], argv[2]);
    #else
    reverseByBlock(argv[1], argv[2]);
    #endif
    
    return 0;
}