# Week 9: Memory Management

## Concept

Memory management allocates physical memory to processes. First-fit and best-fit are contiguous memory allocation strategies. First-fit finds the first hole large enough, while best-fit finds the smallest hole that fits. These strategies affect fragmentation and allocation speed differently.

## Examples

- `first_fit_allocation.cpp` - First-fit memory allocation algorithm
- `best_fit_allocation.cpp` - Best-fit memory allocation algorithm

## Compile

```bash
g++ -std=c++17 -pthread week-9/memory-management/first_fit_allocation.cpp -o week-9/memory-management/first_fit_allocation
g++ -std=c++17 -pthread week-9/memory-management/best_fit_allocation.cpp -o week-9/memory-management/best_fit_allocation
```

## Run

```bash
./week-9/memory-management/first_fit_allocation
./week-9/memory-management/best_fit_allocation
```

## Learning Outcome

Students will understand:
- How memory is allocated to processes
- Trade-offs between first-fit and best-fit
- External fragmentation and its effects
- Memory management strategies in real OSes
