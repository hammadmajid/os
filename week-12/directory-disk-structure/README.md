# Week 12: Directory & Disk Structure

## Concept

Directories provide hierarchical file organization. The directory structure maps filenames to inodes containing file metadata. Understanding directory implementation and disk layout is crucial for file system design.

## Examples

- `list_directory.cpp` - Lists files in a directory
- `simple_directory_table.cpp` - Simulates directory table structure

## Compile

```bash
g++ -std=c++17 -pthread week-12/directory-disk-structure/list_directory.cpp -o week-12/directory-disk-structure/list_directory
g++ -std=c++17 -pthread week-12/directory-disk-structure/simple_directory_table.cpp -o week-12/directory-disk-structure/simple_directory_table
```

## Run

```bash
./week-12/directory-disk-structure/list_directory
./week-12/directory-disk-structure/simple_directory_table
```

## Learning Outcome

Students will understand:
- Directory structure and file lookup
- Inode and directory entry relationships
- How file names map to inodes
- Directory traversal and search
