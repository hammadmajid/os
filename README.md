# Operating Systems Course Project

A comprehensive C++17 implementation of Operating Systems concepts across 15 weeks, designed for Bachelor-level CS students.

## Project Structure

Each week directory contains focused examples demonstrating core OS concepts:

### Week-by-Week Topics

- **Week 1**: OS Introduction - System calls, process creation
- **Week 2**: Process Scheduling - Process states, scheduling algorithms
- **Week 3**: Inter-Process Communication - Pipes, named pipes
- **Week 4**: Multithreading - Thread basics, shared data problems
- **Week 5**: CPU Scheduling - SJF, Round Robin, scheduling algorithms
- **Week 6**: Synchronization & Critical Section - Race conditions, mutexes
- **Week 7**: Synchronization Hardware & Problems - Test-and-set, semaphores
- **Week 8**: Deadlocks - Deadlock scenarios, banker's algorithm
- **Week 9**: Memory Management - First-fit, best-fit allocation
- **Week 10**: Virtual Memory - Paging, page replacement algorithms
- **Week 11**: File Systems - File I/O, memory-mapped files
- **Week 12**: Directory & Disk Structure - Directory management
- **Week 13**: Free Space Management - Bitmap, linked-list allocation
- **Week 14**: Virtual Machines - VM concepts, bytecode interpretation
- **Week 15**: System Protection & Security - File permissions, access control

## Building the Project

### Compile All Examples
```bash
make all
```

### Compile Specific Example
```bash
g++ -std=c++17 -pthread week-1/os-introduction/system_call_demo.cpp -o week-1/os-introduction/system_call_demo
```

### Clean All Executables
```bash
make clean
```

### List All Source Files
```bash
make list
```

## Code Standards

- **Language**: C++17
- **Compiler**: g++ with `-std=c++17 -pthread`
- **No STL Containers**: Use arrays and manual structures
- **System Calls**: fork, pipe, open, read, write, close, wait, etc.
- **Threading**: pthreads or C++17 std::thread
- **Comments**: Only explain difficult OS concepts
- **Code Style**: Clear variable names, minimal complexity

## Running Examples

Each week directory contains a README with specific run instructions:

```bash
cd week-1/os-introduction
./system_call_demo
./process_creation_demo
```

## Learning Outcomes

By studying this project, students will:
- Understand core OS concepts through practical examples
- Learn how processes, threads, and resources work
- Grasp synchronization, scheduling, and memory management
- See real Linux system calls in action
- Develop strong foundation in OS implementation

## Directory Structure

```
os/
├── README.md (this file)
├── Makefile
├── .gitignore
├── week-1/os-introduction/
├── week-2/process-scheduling/
├── week-3/inter-process-communication/
├── week-4/multithreading/
├── week-5/cpu-scheduling/
├── week-6/synchronization-critical-section/
├── week-7/synchronization-hardware-problems/
├── week-8/deadlocks/
├── week-9/memory-management/
├── week-10/virtual-memory/
├── week-11/file-systems/
├── week-12/directory-disk-structure/
├── week-13/free-space-management/
├── week-14/virtual-machines/
└── week-15/system-protection-security/
```

Each week contains:
- `README.md` - Topic overview and instructions
- `*.cpp` - Example implementations
- Compile/run commands in comments

## Make Targets

- `make all` - Compile all C++ files
- `make clean` - Remove all compiled executables
- `make list` - List all source files and directories
- `make help` - Show help information
