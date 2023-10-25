#include <iostream>
#include <mpi.h>

#define MASTER 0

void printVector(int* v, int size)
{
    for (int i = 0; i < size; i++)
        std::cout << v[i] << ("\n "[i == size - 1 ? 0 : 1]);
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status* status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int DATA_COUNT = 3;
    int send[][DATA_COUNT] = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };

    if (rank == MASTER)
    {
        for (int i = 0; i < size; i++) if (i != MASTER)
        {
            MPI_Send(send[i], DATA_COUNT, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    }
    else
    {
        int recvbuf[DATA_COUNT];
        MPI_Recv(recvbuf, DATA_COUNT, MPI_INT, MASTER, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::cout << rank << " - ";
        std::cout << rank << '/' << size << ": ";
        printVector(recvbuf, DATA_COUNT);
    }

    MPI_Finalize();

    return 0;
}
