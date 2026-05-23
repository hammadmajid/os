# Week 13: Free Space Management

## Concept

File systems must track free disk space to allocate blocks for new files. Bitmap allocation uses bits to mark block status, while linked-list allocation chains free blocks together. Each approach has different space and performance characteristics.

## Examples

- `bitmap_free_space.cpp` - Bitmap-based free space management
- `linked_free_space.cpp` - Linked-list based free space management

## Compile

```bash
g++ -std=c++17 -pthread week-13/free-space-management/bitmap_free_space.cpp -o week-13/free-space-management/bitmap_free_space
g++ -std=c++17 -pthread week-13/free-space-management/linked_free_space.cpp -o week-13/free-space-management/linked_free_space
```

## Run

```bash
./week-13/free-space-management/bitmap_free_space
./week-13/free-space-management/linked_free_space
```

## Learning Outcome

Students will understand:
- Bitmap and linked-list free space representations
- Trade-offs between space efficiency and speed
- How to find free blocks efficiently
- Fragmentation issues in free space management
