#include <stdio.h>
#include <stdlib.h>

int main() {
    // Size of the vectors
    int size = 100000000;

    // Allocate memory for vectors on the host
    float *h_a, *h_b, *h_result;
    h_a = (float*)malloc(size * sizeof(float));
    h_b = (float*)malloc(size * sizeof(float));
    h_result = (float*)malloc(size * sizeof(float));

    // Initialize vectors on the host
    for (int i = 0; i < size; ++i) {
        h_a[i] = (float) i * 1e-10f;
        h_b[i] = (float) i * 2.0e-10f;
    }

    for (int i = 0; i < size; i++)
    {
        h_result[i] = h_a[i] + h_b[i];
    }

    for (int i = 0; i < size; ++i) {
        printf("%f ", h_result[i]);
    }
    printf("\n");

    return 0;
}
