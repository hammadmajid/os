# Week 3: Inter-Process Communication

## Concept

Processes often need to communicate and share data. Inter-Process Communication (IPC) mechanisms allow processes to exchange information safely. Pipes are the most common IPC mechanism in Unix, allowing unidirectional data flow between parent and child processes. Named pipes (FIFOs) extend this capability to unrelated processes.

## Examples

- `pipe_parent_child.cpp` - Demonstrates communication via anonymous pipes
- `named_pipe_demo.cpp` - Shows named pipe (FIFO) usage for IPC

## Compile

```bash
g++ -std=c++17 -pthread week-3/inter-process-communication/pipe_parent_child.cpp -o week-3/inter-process-communication/pipe_parent_child
g++ -std=c++17 -pthread week-3/inter-process-communication/named_pipe_demo.cpp -o week-3/inter-process-communication/named_pipe_demo
```

## Run

```bash
./week-3/inter-process-communication/pipe_parent_child
./week-3/inter-process-communication/named_pipe_demo
```

## Learning Outcome

Students will understand:
- How pipes enable communication between processes
- The difference between anonymous and named pipes
- File descriptors for reading and writing
- The parent-child communication pattern
