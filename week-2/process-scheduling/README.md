# Week 2: Process Scheduling

## Concept

Process scheduling determines which process runs on the CPU at any given time. The scheduler uses various algorithms to decide which process gets CPU time. Common metrics include waiting time and turnaround time. Understanding scheduling helps optimize CPU utilization and system responsiveness.

## Examples

- `process_states_demo.cpp` - Demonstrates different process states during execution
- `process_states_parent_child.cpp` - Shows how parent and child processes interact
- `concurrent_execution_demo.cpp` - Illustrates concurrent execution of parent and child
- `process_creation_demo.cpp` - Basic process creation and termination
- `fcfs_process_scheduling.cpp` - First-Come-First-Served scheduling algorithm

## Compile

```bash
g++ -std=c++17 -pthread week-2/process-scheduling/process_states_demo.cpp -o week-2/process-scheduling/process_states_demo
g++ -std=c++17 -pthread week-2/process-scheduling/process_states_parent_child.cpp -o week-2/process-scheduling/process_states_parent_child
g++ -std=c++17 -pthread week-2/process-scheduling/concurrent_execution_demo.cpp -o week-2/process-scheduling/concurrent_execution_demo
g++ -std=c++17 -pthread week-2/process-scheduling/process_creation_demo.cpp -o week-2/process-scheduling/process_creation_demo
g++ -std=c++17 -pthread week-2/process-scheduling/fcfs_process_scheduling.cpp -o week-2/process-scheduling/fcfs_process_scheduling
```

## Run

```bash
./week-2/process-scheduling/process_states_demo
./week-2/process-scheduling/fcfs_process_scheduling
```

## Learning Outcome

Students will understand:
- Process creation and management
- Parent-child process relationships
- The difference between waiting time and turnaround time
- How scheduling algorithms allocate CPU time
