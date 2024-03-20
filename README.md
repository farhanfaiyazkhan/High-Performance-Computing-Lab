# High Performance Computing Lab

Welcome to the High Performance Computing (HPC) Lab repository! This repository contains practicals designed to help you understand and implement various concepts related to high performance computing.

## Practical List

1. Matrix Multiplication Performance Analysis
2. Parallel "Hello World" with MPI
3. Quick Sort with MPI
4. Multithreaded Fibonacci Series with pThreads
5. Process Synchronization with Mutex Locks using pThreads
6. Hello World with OpenMP
7. Multitasking with OpenMP
8. Parallel Calculation of PI/Area of Circle with OpenMP
9. OpenMP Loop Scheduling Demonstrations

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
