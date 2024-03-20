#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ITERATIONS 10000

int shared_variable = 0;
pthread_mutex_t mutex;

void *increment(void *arg)
{
    for (int i = 0; i < ITERATIONS; ++i)
    {
        pthread_mutex_lock(&mutex);
        shared_variable++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *decrement(void *arg)
{
    for (int i = 0; i < ITERATIONS; ++i)
    {
        pthread_mutex_lock(&mutex);
        shared_variable--;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&threads[0], NULL, increment, NULL);
    pthread_create(&threads[1], NULL, decrement, NULL);

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of shared variable: %d\n", shared_variable);

    pthread_mutex_destroy(&mutex);

    return 0;
}
