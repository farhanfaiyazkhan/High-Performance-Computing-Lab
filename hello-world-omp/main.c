#include <omp.h>
#include <stdio.h>

int main()
{
    int num_threads;

    omp_set_num_threads(4);

#pragma omp parallel
    {
        num_threads = omp_get_num_threads();

        int tid = omp_get_thread_num();

        printf("Hello World from thread %d\n", tid);
    }

    printf("Total number of threads: %d\n", num_threads);

    return 0;
}
