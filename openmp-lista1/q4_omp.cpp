#include <stdio.h>
#include <omp.h>
#define N 300000
#define NUM_THREADS 8

int main(void)
{
    int primos = 0;
    #pragma omp parallel num_threads(NUM_THREADS) reduction(+:primos) 
    {
        int start;
        if (omp_get_thread_num() == 0)
            start = 2;
        else
            start = omp_get_thread_num() * N / omp_get_num_threads();
        int end = start + N / omp_get_num_threads();

        for (int i = start; i < end; i++)
        {
            int j = 2;
            while (j < i)
            {
                if (i % j == 0)
                    break;
                j++;
            }
            if (j == i)
            {
                printf("%d\n", i);
                primos++;
            }
        }
    }
    printf("%d primos!\n", primos);

    return 0;
} /*fim-main */
