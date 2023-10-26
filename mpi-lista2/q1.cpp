#include <iostream>
#include <mpi.h>

#define MASTER 0

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int DATA_COUNT = 12;
    int vec[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 11, 12};
    int recvbuf[DATA_COUNT/3];


    MPI_Scatter(vec, DATA_COUNT / 3, MPI_INT, recvbuf, DATA_COUNT / 3, MPI_INT, MASTER, MPI_COMM_WORLD);

    for (int i = 0; i < DATA_COUNT / 3; i++)
    {
        std::cout << recvbuf[i] << " ";
    }
    std::cout << std::endl;

    MPI_Finalize();

    return 0;
}
