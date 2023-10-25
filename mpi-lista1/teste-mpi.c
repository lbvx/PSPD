#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long int N = 1LL << 30;  // Sum numbers from 1 to N
    long long int local_sum = 0;
    long long int total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate the range for each process
    int chunk_size = N / size;
    int start = rank * chunk_size + 1;
    int end = (rank == size - 1) ? N : start + chunk_size - 1;

    // Calculate the local sum
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }

    // Reduce local sums to the total sum
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Output the result from the root process
    if (rank == 0) {
        printf("Total sum: %lld\n", total_sum);
    }

    MPI_Finalize();

    return 0;
}
