#include <iostream>
#include <mpi.h>

#define MASTER 0

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buf1 = 0;
    int buf2;
    if (rank == MASTER)
        std::cin >> buf1;

    MPI_Bcast(&buf1, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    buf2 = buf1 + 2;
    MPI_Send(&buf2, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);

    if (rank == MASTER)
    {
        for (int i = 0; i < size; i++)
        {
            MPI_Recv(&buf1, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << i << '/' << size << ": " << buf1 << std::endl;
        }
    }

    MPI_Finalize();

    return 0;
}
