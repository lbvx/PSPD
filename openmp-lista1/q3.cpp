#include <iostream>
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    long long n;
    unsigned int n_threads;

    std::cout << "Quantidade de elementos: ";
    std::cin >> n;
    std::cout << "Nº de threads: ";
    std::cin >> n_threads;
    std::cout << std::endl;
    
    #pragma omp parallel num_threads(n_threads)
    {
        long long count = 0;
        #pragma omp for
        for (long long i = 0; i < n; i++)
            count++;
        printf("T%d - %lld elementos\n", omp_get_thread_num(), count);
    }

    return 0;
}
