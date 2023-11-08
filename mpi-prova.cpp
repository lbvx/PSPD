// Compilar com mpic++
// Rodar com mpirun -np 3

#include <iostream>
#include <mpi.h>
#include <ctime>

#define MASTER 0
#define SLAVE1 1
#define SLAVE2 2
#define DIM 4

void printMatrix(int m[][DIM])
{
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            std::cout << m[i][j] << "\n "[j == DIM - 1 ? 0 : 1];
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Matrizes predefinidas
    // int A[][DIM] = {
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8},
    //     {9, 10, 11, 12},
    //     {13, 14, 15, 16}
    // };
    // int B[][DIM] = {
    //     {16, 15, 14, 13},
    //     {12, 11, 10, 9},
    //     {8, 7, 6, 5},
    //     {4, 3, 2, 1}
    // };

    // Matrizes aleatorias
    int A[DIM][DIM];
    int B[DIM][DIM];

    std::srand(std::time(0));
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            A[i][j] = std::rand() % 8;
            B[i][j] = std::rand() % 8;
        }
    }
    
    int C[DIM][DIM];
    // MASTER
    if (rank == MASTER)
    {
        int linha[DIM];
        for (int i = 0; i < DIM; i += 2)
        {
            // Envia linhas da matriz A e B pros slaves
            MPI_Send(A[i], DIM, MPI_INT, SLAVE1, 1, MPI_COMM_WORLD);
            MPI_Send(B[i], DIM, MPI_INT, SLAVE1, 1, MPI_COMM_WORLD);

            MPI_Send(A[i + 1], DIM, MPI_INT, SLAVE2, 2, MPI_COMM_WORLD);
            MPI_Send(B[i + 1], DIM, MPI_INT, SLAVE2, 2, MPI_COMM_WORLD);
            
            // Recebe resultado da soma e guarda na matriz C
            MPI_Recv(linha, DIM, MPI_INT, SLAVE1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < DIM; j++)
                C[i][j] = linha[j];

            MPI_Recv(linha, DIM, MPI_INT, SLAVE2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < DIM; j++)
                C[i + 1][j] = linha[j];
        }
        // Saída
        std::cout << "A =\n";
        printMatrix(A);
        std::cout << "\nB = \n";
        printMatrix(B);
        std::cout << "\nC = A + B =\n";
        printMatrix(C);
    }
    // SLAVE
    else
    {
        int linhaA[DIM], linhaB[DIM], linhaC[DIM];
        for (int i = 0; i < DIM / 2; i++)
        {
            // Recebe linhas das matrizes A e B
            MPI_Recv(linhaA, DIM, MPI_INT, MASTER, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(linhaB, DIM, MPI_INT, MASTER, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Calcula e envia o resultado das somas para o Master
            for (int i = 0; i < DIM; i++)
                linhaC[i] = linhaA[i] + linhaB[i];

            MPI_Send(linhaC, DIM, MPI_INT, MASTER, rank, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}
