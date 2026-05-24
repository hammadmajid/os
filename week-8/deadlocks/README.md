# Week 8: Deadlocks

## Concept

A deadlock occurs when processes are blocked indefinitely, each waiting for resources held by others. Deadlocks require four conditions: mutual exclusion, hold and wait, no preemption, and circular wait. The Banker's Algorithm prevents deadlock by checking if resource allocation is safe before granting requests.

## Examples

- `deadlock_demo.cpp` - Demonstrates deadlock scenario with circular wait
- `bankers_algorithm.cpp` - Shows deadlock prevention using Banker's Algorithm

## Compile

```bash
g++ -std=c++17 -pthread week-8/deadlocks/deadlock_demo.cpp -o week-8/deadlocks/deadlock_demo
g++ -std=c++17 -pthread week-8/deadlocks/bankers_algorithm.cpp -o week-8/deadlocks/bankers_algorithm
```

## Run

```bash
./week-8/deadlocks/deadlock_demo
./week-8/deadlocks/bankers_algorithm
```

## Learning Outcome

Students will understand:
- The four necessary conditions for deadlock
- How circular waits create deadlock situations
- Deadlock prevention vs avoidance strategies
- How the Banker's Algorithm ensures safe resource allocation
