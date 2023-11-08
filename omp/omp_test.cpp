#include <stdio.h>
#include <iostream>
#include <omp.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

int main() {
    int data[ARRAY_SIZE];
    int sum = 0;

    // Initialize the data array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = i + 1;
    }

    // Enable parallelism with OpenMP
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int local_sum = 0;

        // Distribute the work among threads using a parallel for loop
        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            local_sum += data[i];
        }

        // Each thread has its own local_sum, so we need to combine them
        // using a critical section
        #pragma omp critical
        sum += local_sum;
    }

    std::cout << "The sum of elements is: " << sum << std::endl; 

    return 0;
}
