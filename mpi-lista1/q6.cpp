#include <iostream>
#include <mpi.h>

#define MASTER 0

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int DATA_COUNT = 1;
    int token = (1 << 29) - 1;
    int buf;

    int dest = (rank + 1) % size;
    int src = (rank - 1);
    if (rank == MASTER)
    {
        src = size - 1;
        MPI_Send(&token, DATA_COUNT, MPI_INT, dest, rank, MPI_COMM_WORLD);

        std::cout << rank << " - ";
        std::cout << "Enviando para " << dest << std::endl;        

        MPI_Recv(&buf, DATA_COUNT, MPI_INT, src, src, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << rank << " - ";
        std::cout << "Recebeu de " << src << " / Token = " << buf <<std::endl;        
    }
    else
    {
        MPI_Recv(&buf, DATA_COUNT, MPI_INT, src, src, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::cout << rank << " - ";
        std::cout << "Recebeu de " << src << ", Enviando para " << dest << std::endl;

        MPI_Send(&buf, DATA_COUNT, MPI_INT, dest, rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
