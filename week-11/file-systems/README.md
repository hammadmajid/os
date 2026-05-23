# Week 11: File Systems

## Concept

File systems organize data storage on disk. Files provide abstraction for persistent data, and directories provide hierarchical organization. File I/O operations read and write data. Memory-mapped files allow treating files as memory for efficient access.

## Examples

- `file_read_write.cpp` - Basic file I/O operations
- `mmap_demo.cpp` - Memory-mapped file demonstration

## Compile

```bash
g++ -std=c++17 -pthread week-11/file-systems/file_read_write.cpp -o week-11/file-systems/file_read_write
g++ -std=c++17 -pthread week-11/file-systems/mmap_demo.cpp -o week-11/file-systems/mmap_demo
```

## Run

```bash
./week-11/file-systems/file_read_write
./week-11/file-systems/mmap_demo
```

## Learning Outcome

Students will understand:
- File creation, reading, and writing
- File descriptors and their role
- Memory-mapped files for efficient I/O
- File system operations at system call level
