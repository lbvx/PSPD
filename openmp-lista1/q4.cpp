#include <stdio.h>
#include <omp.h>
#define N 300000

int main(void)
{
    int i;
    int primos = 0;
    for (i = N; i > 1; i--)
    {
        int j = 2;
        while (j < i)
        {
            if (i % j == 0)
                break;
            j++;
        } /* fim-while */
        if (j == i)
        {
            printf("%d\n", i);
            primos++;
        }
    } /* fim-for */
    printf("%d primos!\n", primos);
    return 0;
} /*fim-main */
