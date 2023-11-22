#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define MAX 1000

int main()
{
    char texto_base[] = "abcdefghijklmnopqrstuvwxyz 1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int *indice = malloc(sizeof(int));
    *indice = 0;

    struct timeval tv;
    int number, tmp_index, i;

    // paraleliza o for entre 3 threads, cada uma realizara o loop original ~MAX/3 vezes
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
        for (int cont = 0; cont < MAX; cont++)
        {
            gettimeofday(&tv, NULL);
            number = ((tv.tv_usec / 47) % 3) + 1;   // 1 2 ou 3, pseudoaleatorio
            tmp_index = *indice;
            for (int i = 0; i < number; i++)
                if ( !(tmp_index + i > sizeof(texto_base)) )
                    fprintf(stderr, "%c", texto_base[tmp_index + i]);
            *indice = tmp_index + i;
            if (tmp_index + i > sizeof(texto_base))
            {
                fprintf(stderr, "\n");
                *indice = 0;
            }
        }
    }
    printf("\n");

    return 0;
}