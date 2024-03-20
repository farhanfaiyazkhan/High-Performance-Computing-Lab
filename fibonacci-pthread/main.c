#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadArgs
{
    int n;
    int *arr;
};

void *fib(void *arg)
{
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int n = args->n;
    int *arr = args->arr;
    arr[0] = 0;
    arr[1] = 1;

    if (n > 1)
    {
        for (int i = 2; i < n; i++)
        {
            arr[i] = arr[i - 1] + arr[i - 2];
        }
    }

    pthread_exit(NULL);
}

int main()
{
    int n;
    printf("Enter a number to print Fibonacci: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    pthread_t tid;
    struct ThreadArgs args;
    args.n = n;
    args.arr = arr;

    pthread_create(&tid, NULL, fib, (void *)&args);

    pthread_join(tid, NULL);

    printf("The resultant Fibonacci series is: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}