#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 1000000000

int main()
{
    double step = 1.0 / NUM_STEPS;
    double sum = 0.0;
    double x;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < NUM_STEPS; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = sum * step;

    printf("Approximate value of PI: %f\n", pi);
    printf("Approximate value of Area of Circle: %f\n", pi * pi);

    return 0;
}
