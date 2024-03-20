#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000
void multiplyMatrices(int firstMatrix[N][N], int secondMatrix[N][N],
                      int result[N][N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int sum = 0;
            for (int k = 0; k < N; ++k)
            {
                sum += firstMatrix[i][k] * secondMatrix[k][j];
            }
            result[i][j] = sum;
        }
    }
}
int main()
{
    int(*firstMatrix)[N] = malloc(sizeof(int[N][N]));
    int(*secondMatrix)[N] = malloc(sizeof(int[N][N]));
    int(*result)[N] = malloc(sizeof(int[N][N]));
    clock_t start_time = clock();
    multiplyMatrices(firstMatrix, secondMatrix, result);
    clock_t end_time = clock();
    printf("Execution Time: %f seconds\n", ((double)(end_time -
                                                     start_time)) /
                                               CLOCKS_PER_SEC);
    free(firstMatrix);
    free(secondMatrix);
    free(result);
    return 0;
}