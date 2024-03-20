#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 1000000

int partition(int *arr, int low, int high)
{
    int pivot = arr[low];
    int i = low + 1;
    int j = high;
    int temp;
    do
    {
        while (arr[i] <= pivot)
            i++;
        while (arr[j] > pivot)
            j--;

        if (j > i)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } while (j > i);

    temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    return j;
}

int hoare_partition(int *arr, int low, int high)
{
    int mid = (low + high) / 2;
    int pivot = arr[mid];

    int j, temp;

    temp = arr[mid];
    arr[mid] = arr[high];
    arr[high] = temp;

    int i = low - 1;
    for (j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quicksort(int *number, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(number, low, high);
        quicksort(number, low, pivot - 1);
        quicksort(number, pivot + 1, high);
    }
}

int quicksort_recursive(int *arr, int arrSize, int currProcRank, int maxRank, int rankIndex)
{
    MPI_Status status;

    int shareProc = currProcRank + pow(2, rankIndex);
    rankIndex++;

    if (shareProc > maxRank)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        quicksort(arr, 0, arrSize - 1);
        return 0;
    }

    int j = 0;
    int pivotIndex;
    pivotIndex = hoare_partition(arr, j, arrSize - 1);

    if (pivotIndex <= arrSize - pivotIndex)
    {
        MPI_Send(arr, pivotIndex, MPI_INT, shareProc, pivotIndex, MPI_COMM_WORLD);
        quicksort_recursive((arr + pivotIndex + 1), (arrSize - pivotIndex - 1), currProcRank, maxRank, rankIndex);
        MPI_Recv(arr, pivotIndex, MPI_INT, shareProc, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }
    else
    {
        MPI_Send((arr + pivotIndex + 1), (arrSize - pivotIndex - 1), MPI_INT, shareProc, pivotIndex + 1, MPI_COMM_WORLD);
        quicksort_recursive(arr, pivotIndex, currProcRank, maxRank, rankIndex);
        MPI_Recv((arr + pivotIndex + 1), (arrSize - pivotIndex - 1), MPI_INT, shareProc, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }
}

int main(int argc, char *argv[])
{
    int unsorted_array[SIZE];
    int array_size = SIZE;
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Creating Random List of %d elements\n", SIZE);
        for (int j = 0; j < SIZE; j++)
        {
            unsorted_array[j] = (int)rand() % 1000;
        }
        printf("Created\n");
    }

    int rankPower = 0;
    while (pow(2, rankPower) <= rank)
        rankPower++;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_timer, finish_timer;

    if (rank == 0)
    {
        start_timer = MPI_Wtime();
        quicksort_recursive(unsorted_array, array_size, rank, size - 1, rankPower);
    }
    else
    {
        MPI_Status status;
        int subarray_size;

        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_INT, &subarray_size);
        int source_process = status.MPI_SOURCE;
        int subarray[subarray_size];
        MPI_Recv(subarray, subarray_size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        quicksort_recursive(subarray, subarray_size, rank, size - 1, rankPower);
        MPI_Send(subarray, subarray_size, MPI_INT, source_process, 0, MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
        finish_timer = MPI_Wtime();
        printf("Total time for %d Clusters: %2.2f sec \n", size, finish_timer - start_timer);

        printf("Checking..\n");
        bool error = false;
        int i = 0;
        for (i = 0; i < SIZE - 1; i++)
        {
            if (unsorted_array[i] > unsorted_array[i + 1])
            {
                error = true;
                printf("error in i = %d \n", i);
            }
        }

        if (error)
        {
            printf("Error.. Not sorted correctly\n");
        }
        else
            printf("Correct\n");
    }

    MPI_Finalize();
    return 0;
}
