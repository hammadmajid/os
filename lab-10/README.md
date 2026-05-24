# Lab 10 Implementation of Deadlock Detection Algorithm in C+

## Task 1

A system has 3 processes (P0, P1, P2) and 3 resource types (A, B, C).
Allocation Matrix
P0 → 0 1 0
P1 → 2 0 0
P2 → 3 0 3
Request Matrix
P0 → 0 0 0
P1 → 2 0 2
P2 → 0 0 0
Available Resources
0 0 0 Apply Deadlock Detection Algorithm
Find which processes can complete
Identify deadlocked processes
Task 2: system has 4 processes (P0–P3) and 3 resources (A, B, C). Given:
Allocation Matrix
P0 → 1 0 1
P1 → 2 1 0
P2 → 3 0 2
P3 → 0 1 1
Request Matrix
P0 → 1 1 0
P1 → 0 1 1
P2 → 1 0 0
P3 → 0 0 1
Available Resources
1 1 1
Task:
Check if system is in safe state
Find safe sequence (if exists)
If not safe, identify deadlock

## Task 2

A system has 3 processes and 3 resources. Given:
Allocation Matrix
P0 → 0 0 1
P1 → 1 2 0
P2 → 2 0 1
Request Matrix
P0 → 1 0 0
P1 → 0 1 1
P2 → 1 1 0
Available Resources
1 1 0
Task:
Apply deadlock detection step by step
Show how resources are released
Identify final deadlocked processes
