# Week 1: Operating System Introduction

## Concept

An Operating System is a software layer that manages hardware resources and provides services to applications. This week covers fundamental OS concepts including system calls, process creation, and how user programs interact with the kernel.

System calls are the primary mechanism through which application programs request services from the OS kernel. Common system calls include `fork()` for process creation, `exec()` for program execution, and `wait()` for synchronization.

## Examples

- `system_call_demo.cpp` - Demonstrates basic system calls and process information retrieval
- `process_creation_demo.cpp` - Shows how processes are created using fork() and their relationship

## Compile

```bash
g++ -std=c++17 -pthread week-1/os-introduction/system_call_demo.cpp -o week-1/os-introduction/system_call_demo
g++ -std=c++17 -pthread week-1/os-introduction/process_creation_demo.cpp -o week-1/os-introduction/process_creation_demo
```

## Run

```bash
./week-1/os-introduction/system_call_demo
./week-1/os-introduction/process_creation_demo
```

## Learning Outcome

Students will understand:
- How system calls bridge application and kernel code
- The parent-child relationship between processes
- Basic process creation using fork()
- How to retrieve process identifiers (PID, PPID)
