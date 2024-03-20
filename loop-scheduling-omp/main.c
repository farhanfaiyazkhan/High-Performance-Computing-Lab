#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 20

int main()
{
    int i, tid;

    printf("Default loop scheduling:\n");
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
#pragma omp for
        for (i = 0; i < NUM_ITERATIONS; i++)
        {
            printf("Thread %d: i = %d\n", tid, i);
        }
    }

    printf("\nStatic loop scheduling:\n");
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
#pragma omp for schedule(static)
        for (i = 0; i < NUM_ITERATIONS; i++)
        {
            printf("Thread %d: i = %d\n", tid, i);
        }
    }

    printf("\nDynamic loop scheduling:\n");
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
#pragma omp for schedule(dynamic)
        for (i = 0; i < NUM_ITERATIONS; i++)
        {
            printf("Thread %d: i = %d\n", tid, i);
        }
    }

    return 0;
}
