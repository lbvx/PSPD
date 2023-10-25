#include <iostream>
#include <mpi.h>

#define MASTER 0

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int in = 0;
    if (rank == MASTER)
        std::cin >> in;

    MPI_Bcast(&in, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    std::cout << rank << '/' << size << ": " << in << std::endl;

    MPI_Finalize();

    return 0;
}
