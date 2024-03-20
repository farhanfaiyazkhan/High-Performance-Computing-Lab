#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 10000
#define NUM_THREADS 4

int main()
{
    int i, sum = 0;
    int arr[ARRAY_SIZE];

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = i + 1;
    }

#pragma omp parallel num_threads(NUM_THREADS) reduction(+ : sum)
    {
        int thread_id = omp_get_thread_num();
        int chunk_size = ARRAY_SIZE / omp_get_num_threads();
        int start = thread_id * chunk_size;
        int end = (thread_id == omp_get_num_threads() - 1) ? ARRAY_SIZE : start + chunk_size;

        for (i = start; i < end; i++)
        {
            sum += arr[i];
        }
    }

    printf("Sum of elements in the array: %d\n", sum);

    return 0;
}
