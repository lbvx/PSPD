#include <iostream>
#include <stdio.h>
#include <omp.h>

#define MAX 10000000
#define NUM_THREADS 4

int main() {
    int alvo = 1;
    int sum = 0;

    FILE *fd;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        fd = fopen("rand.txt", "r");

        // ajustar o offset baseado no omp_get_thread_num() e omp_get_num_threads()
        int qtd = MAX / omp_get_num_threads();
        long offset = omp_get_thread_num() * qtd; 
        fseek(fd, offset, SEEK_SET);

        // ler os pedaços do arquivo em cada thread e comparar com alvo
        int localSum = 0;
        char* linha = (char*) malloc(sizeof(char) * 9);
        for (int i = 0; i < qtd; i++)
        {
            int num;

            // std::cout << "thread" << omp_get_thread_num() << "-" << offset << std::endl;
            fread(linha, sizeof(char), 9, fd);

            if (omp_get_thread_num() == 1)
                std::cout << "thread" << omp_get_thread_num() << "-" << linha << std::endl;

            num = atoi(linha);

            if (num == alvo)
                localSum++;
        }
        
        #pragma omp critical
        sum += localSum;
    }

    std::cout << sum << std::endl;

    return 0;
}
