# Week 5: CPU Scheduling

## Concept

CPU scheduling algorithms determine which ready process executes next. Different algorithms optimize for different goals: Shortest Job First (SJF) minimizes average waiting time, Round Robin ensures fairness with time quantum. Scheduling is crucial for system performance and responsiveness.

## Examples

- `sjf_scheduling.cpp` - Shortest Job First scheduling algorithm
- `round_robin_scheduling.cpp` - Round Robin scheduling with time quantum

## Compile

```bash
g++ -std=c++17 -pthread week-5/cpu-scheduling/sjf_scheduling.cpp -o week-5/cpu-scheduling/sjf_scheduling
g++ -std=c++17 -pthread week-5/cpu-scheduling/round_robin_scheduling.cpp -o week-5/cpu-scheduling/round_robin_scheduling
g++ -std=c++17 -pthread week-5/cpu-scheduling/fcfs_scheduling.cpp -o week-5/cpu-scheduling/fcfs_scheduling
```

## Run

```bash
./week-5/cpu-scheduling/sjf_scheduling
./week-5/cpu-scheduling/round_robin_scheduling
./week-5/cpu-scheduling/fcfs_scheduling
```

## Learning Outcome

Students will understand:
- How different scheduling algorithms affect waiting and turnaround times
- The trade-off between fairness and efficiency
- How time quantum affects round robin performance
- Metrics for evaluating scheduler quality
