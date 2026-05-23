# Week 4: Multithreading

## Concept

Multithreading allows multiple threads of execution within a single process, sharing the same memory space. This enables concurrent execution and is useful for I/O operations and multicore systems. However, shared memory introduces challenges like race conditions and data corruption when multiple threads access shared resources simultaneously.

## Examples

- `pthread_basic.cpp` - Demonstrates basic thread creation and synchronization
- `thread_shared_data_problem.cpp` - Shows race conditions with unsynchronized shared data

## Compile

```bash
g++ -std=c++17 -pthread week-4/multithreading/pthread_basic.cpp -o week-4/multithreading/pthread_basic
g++ -std=c++17 -pthread week-4/multithreading/thread_shared_data_problem.cpp -o week-4/multithreading/thread_shared_data_problem
```

## Run

```bash
./week-4/multithreading/pthread_basic
./week-4/multithreading/thread_shared_data_problem
```

## Learning Outcome

Students will understand:
- How to create and join threads
- Thread synchronization basics
- How race conditions occur with shared data
- The importance of mutex protection
