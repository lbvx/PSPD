#include <stdio.h>
#include <stdlib.h>

// CUDA kernel to add two numbers
__global__ void addKernel(float a, float b, float *result) {
    *result = a + b;
    printf("blockId = %d; threadId = %d; blockDim = %d!\n", blockIdx.x, threadIdx.x, blockDim.x);
}

int main() {
    // Input values
    float host_a = 3.0f;
    float host_b = 4.0f;

    // Result variable on the host
    float host_result;

    // Result variable on the device
    float *device_result;
    cudaMalloc((void**)&device_result, sizeof(float));

    // Launch the add kernel with one block and one thread
    // <<<NumBlocks, BlockSize>>>   contem o numero de blocos e o numero de threads por bloco, respectivamente
    addKernel<<<2, 3>>>(host_a, host_b, device_result);

    // Copy the result back to the host
    cudaMemcpy(&host_result, device_result, sizeof(float), cudaMemcpyDeviceToHost);

    // Print the result
    printf("Result of %.2f + %.2f on GPU: %.2f\n", host_a, host_b, host_result);

    // Free memory
    cudaFree(device_result);

    return 0;
}
