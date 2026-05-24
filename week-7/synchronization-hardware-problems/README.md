# Week 7: Synchronization Hardware & Problems

## Concept

Hardware synchronization primitives like test-and-set provide atomic operations for building locks and semaphores. Semaphores are counters that control access to shared resources, enabling producer-consumer synchronization patterns. These low-level mechanisms are fundamental to solving classical synchronization problems.

## Examples

- `test_and_set_simulation.cpp` - Simulates hardware test-and-set instruction
- `producer_consumer_semaphore.cpp` - Producer-consumer pattern using semaphores

## Compile

```bash
g++ -std=c++17 -pthread week-7/synchronization-hardware-problems/test_and_set_simulation.cpp -o week-7/synchronization-hardware-problems/test_and_set_simulation
g++ -std=c++17 -pthread week-7/synchronization-hardware-problems/producer_consumer_semaphore.cpp -o week-7/synchronization-hardware-problems/producer_consumer_semaphore
```

## Run

```bash
./week-7/synchronization-hardware-problems/test_and_set_simulation
./week-7/synchronization-hardware-problems/producer_consumer_semaphore
```

## Learning Outcome

Students will understand:
- How test-and-set enables atomic lock operations
- Semaphore semantics and counting semaphores
- Producer-consumer synchronization patterns
- How hardware support simplifies synchronization
