#include <iostream>
#include <stdio.h>
#include <omp.h>

#define MAX 10000000
#define NUM_THREADS 4

int main() {
    int alvo = 1;
    int sum = 0;

    FILE *fd;

    #pragma omp parallel
    {
        fd = fopen("rand.txt", "r");
        // ajustar o offset baseado no omp_get_thread_num() e omp_get_num_threads()
        long offset = ...;
        fseek(fd, offset, SEEK_SET);
        // ler os pedaços do arquivo em cada thread e comparar com alvo
    }

    std::cout << sum << std::endl;

    return 0;
}
