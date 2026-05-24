# Week 6: Synchronization & Critical Section

## Concept

A critical section is a code segment where shared resources are accessed. Multiple threads entering the critical section simultaneously causes race conditions and data corruption. Synchronization mechanisms like mutexes ensure only one thread enters the critical section at a time, maintaining data consistency and preventing race conditions.

## Examples

- `race_condition.cpp` - Demonstrates unsynchronized access causing race conditions
- `mutex_solution.cpp` - Shows how mutex prevents race conditions

## Compile

```bash
g++ -std=c++17 -pthread week-6/synchronization-critical-section/race_condition.cpp -o week-6/synchronization-critical-section/race_condition
g++ -std=c++17 -pthread week-6/synchronization-critical-section/mutex_solution.cpp -o week-6/synchronization-critical-section/mutex_solution
```

## Run

```bash
./week-6/synchronization-critical-section/race_condition
./week-6/synchronization-critical-section/mutex_solution
```

## Learning Outcome

Students will understand:
- What critical sections are and why they matter
- How race conditions corrupt shared data
- How mutexes protect critical sections
- The importance of proper synchronization
