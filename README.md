# High Performance Computing Lab

Welcome to the High Performance Computing (HPC) Lab repository! This repository contains practicals designed to help you understand and implement various concepts related to high performance computing.

## Practical List

1. [Matrix Multiplication Performance Analysis](#matrix-multiplication-performance-analysis)
2. [Parallel "Hello World" with MPI](#parallel-hello-world-with-mpi)
3. [Quick Sort with MPI](#quick-sort-with-mpi)
4. [Multithreaded Fibonacci Series with pThreads](#multithreaded-fibonacci-series-with-pthreads)
5. [Process Synchronization with Mutex Locks using pThreads](#process-synchronization-with-mutex-locks-using-pthreads)
6. [Hello World with OpenMP](#hello-world-with-openmp)
7. [Multitasking with OpenMP](#multitasking-with-openmp)
8. [Parallel Calculation of PI/Area of Circle with OpenMP](#parallel-calculation-of-piarea-of-circle-with-openmp)
9. [OpenMP Loop Scheduling Demonstrations](#openmp-loop-scheduling-demonstrations)

### How to Compile and Run Code

To run MPI code you need to first install MPICH and then compile using following commands:
```bash
sudo apt install mpich
mpicc main.c -o main
```

To compile OpenMP code, you can use the following command:
```bash
gcc main.c -o main -fopenmp
```

To compile POSIX Thread code, you can use the following command:
```bash
gcc main.c -o main -pthread
```

Finally, run the compiled executable file created using:
```bash
./main
```

Feel free to explore each practical and contribute to the understanding of high performance computing concepts! If you have any questions or suggestions, please don't hesitate to reach out. Happy coding! 🚀
