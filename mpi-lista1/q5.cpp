#include <iostream>
#include <string.h>
#include <mpi.h>

#define MASTER 0

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int DATA_COUNT = 100;
    char buf[100];

    if (rank == MASTER)
    {
        for (int i = 0; i < size; i++) if (i != MASTER)
        {
            MPI_Recv(buf, DATA_COUNT, MPI_CHAR, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::cout << rank << " - ";
            std::cout << i << '/' << size << ": " << buf << std::endl;            
        }
    }
    else
    {
        strcpy(buf, "Oi, Estou Vivo!");
        MPI_Send(buf, DATA_COUNT, MPI_CHAR, MASTER, rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
