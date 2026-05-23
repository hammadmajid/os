# Week 10: Virtual Memory

## Concept

Virtual memory enables processes to use more memory than physically available by using disk storage. Paging divides memory into fixed-size pages, which can be swapped between RAM and disk. Page replacement algorithms determine which page to evict when memory is full.

## Examples

- `paging_simulation.cpp` - Simulates page table and address translation
- `fifo_page_replacement.cpp` - First-In-First-Out page replacement algorithm

## Compile

```bash
g++ -std=c++17 -pthread week-10/virtual-memory/paging_simulation.cpp -o week-10/virtual-memory/paging_simulation
g++ -std=c++17 -pthread week-10/virtual-memory/fifo_page_replacement.cpp -o week-10/virtual-memory/fifo_page_replacement
```

## Run

```bash
./week-10/virtual-memory/paging_simulation
./week-10/virtual-memory/fifo_page_replacement
```

## Learning Outcome

Students will understand:
- Virtual to physical address translation
- Page table organization
- Page replacement strategies and their performance
- How virtual memory enables memory overallocation
