// compilar com mpicc <nome_do_arquivo> -o <nome_do_binario>
// rodar com mpirun -np 3 <nome_do_binario>

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define MAX 1000

int main(int argc, char *argv[])
{
    char texto_base[] = "abcdefghijklmnopqrstuvwxyz 1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int *indice = malloc(sizeof(int));
    *indice = 0;

    struct timeval tv;
    int number, tmp_index, i;

    // inicializa MPI
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // divide tarefa igualmente
    int max;
    if (rank == 0)
        max = (MAX / size) + (MAX % size);
    else
        max = MAX / size;

    // cada processo irá realizar o for MAX / 3 vezes, exceto pelo de rank 0 que realizará os restantes (caso a divisão não seja exata)
    for (int cont = 0; cont < max; cont++)
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
        cont++;
    }
    MPI_Finalize();

    printf("\n");

    return 0;
}
