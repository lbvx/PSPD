#include <stdio.h>

// CUDA kernel to add two vectors
__global__ void vectorAddition(float *a, float *b, float *result, int size) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < size) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    // Size of the vectors
    int size = 1000000;

    // Allocate memory for vectors on the host
    float *h_a, *h_b, *h_result;
    h_a = (float*)malloc(size * sizeof(float));
    h_b = (float*)malloc(size * sizeof(float));
    h_result = (float*)malloc(size * sizeof(float));

    // Initialize vectors on the host
    for (int i = 0; i < size; ++i) {
        h_a[i] = (float) i;
        h_b[i] = (float) i * 2.0f;
    }

    // Allocate memory for vectors on the device
    float *d_a, *d_b, *d_result;
    cudaMalloc((void**)&d_a, size * sizeof(float));
    cudaMalloc((void**)&d_b, size * sizeof(float));
    cudaMalloc((void**)&d_result, size * sizeof(float));

    // Copy vectors from host to device
    cudaMemcpy(d_a, h_a, size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size * sizeof(float), cudaMemcpyHostToDevice);

    // Set up grid and block sizes
    int blockSize = 256;
    int numBlocks = (size + blockSize - 1) / blockSize;

    // Launch the vector addition kernel
    vectorAddition<<<numBlocks, blockSize>>>(d_a, d_b, d_result, size);

    // Copy result vector from device to host
    cudaMemcpy(h_result, d_result, size * sizeof(float), cudaMemcpyDeviceToHost);

    // Verify the results
    for (int i = 0; i < size; ++i) {
        printf("%f ", h_result[i]);
    }
    printf("\n");

    printf("Vector addition on GPU completed successfully!\n");

    // Free memory
    free(h_a);
    free(h_b);
    free(h_result);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_result);

    return 0;
}
