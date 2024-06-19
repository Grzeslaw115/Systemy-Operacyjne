#include <stdio.h>
#include <dlfcn.h>
#include "collatz.h"

#define MAX_ITER 1000

void testNumbers(int (*testFunc)(int, int), int* numbers, int num_numbers) {
    for (int i = 0; i < num_numbers; i++) {
        int result = testFunc(numbers[i], MAX_ITER);
        if (result != -1) {
            printf("Liczba %d zbiegła do 1 po %d iteracjach.\n", numbers[i], result);
        } else {
            printf("Liczba %d nie zbiegła do 1 w maksymalnej liczbie iteracji.\n", numbers[i]);
        }
    }
}

int main() {
    int test_numbers[] = {20, 14, 31, 12, 17, 21, 30, 1, 25, 19};
    int num_numbers = sizeof(test_numbers) / sizeof(test_numbers[0]);

    #ifndef DYNAMIC
    testNumbers(test_collatz_convergence, test_numbers, num_numbers);
    #else
    void *handle = dlopen("./libcollatz.so", RTLD_LAZY);
    if (!handle) {
        printf("Nie udalo sie otworzyc biblioteki.\n");
        return 1;
    }

    int (*dyn_test_collatz_convergence)(int, int) = (int (*)(int, int))dlsym(handle, "test_collatz_convergence");
    if (!dyn_test_collatz_convergence) {
        printf("Nie udalo sie znalezc funkcji test_collatz_convergence.\n");
        dlclose(handle);
        return 1;
    }

    testNumbers(dyn_test_collatz_convergence, test_numbers, num_numbers);
    dlclose(handle);
    #endif
    
    return 0;
}