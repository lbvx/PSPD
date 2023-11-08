#include <iostream>
#include <stdio.h>
#include <omp.h>

#define MAX 10000000
#define NUM_THREADS 4

int main() {
    int alvo = 1;
    int sum = 0;

    // isso é mais lerdo pq o scanf tem que ficar abrindo e fechando o arquivo
    #pragma omp parallel for reduction (+:sum)
    for (int i = 0; i < MAX; i++)
    {
        int num;
        scanf("%d", &num);
        if (num == alvo)
            sum++;
    }

    std::cout << sum << std::endl;

    return 0;
}
