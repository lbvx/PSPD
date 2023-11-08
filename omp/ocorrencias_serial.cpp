#include <iostream>
#include <stdio.h>
#include <omp.h>

#define MAX 10000000
#define NUM_THREADS 4

int main() {
    int alvo = 1;
    int sum = 0;

    for (int i = 0; i < MAX; i++)
    {
        int num;
        // std::cin >> num;
        scanf("%d", &num);
        sum += (num == alvo) ? 1 : 0; 
    }

    std::cout << sum << std::endl;

    return 0;
}
