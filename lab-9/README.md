# Lab 9 Implementation of deadlock creation and avoidance in C++

## task 1

Find the situation to implement deadlock occurrence and then apply deadlock avoidance.

## task 2

you are required to implement a system in C++ that first demonstrates the creation of a deadlock using multiple threads and shared resources. For example, simulate two processes where each process locks one resource and waits indefinitely for another, resulting in a circular wait condition. After demonstrating deadlock, modify your program to implement a deadlock avoidance technique. You may use strategies such as resource ordering, Banker’s Algorithm, or proper synchronization using mutex locks to prevent circular waiting conditions. The updated program should ensure that all processes complete execution without getting stuck.
Finally, compare both implementations and explain how the avoidance technique successfully prevents deadlock. Also analyze system behavior in terms of resource utilization and process execution.

# Task 3

You are developing a banking system where multiple transactions (threads) require access to shared resources such as account records and transaction logs. Sometimes, two transactions may lock different resources and wait for each other, causing a deadlock. Implement a C++ program that first demonstrates this deadlock situation. Then, modify the system using a such as resource ordering or Banker’s Algorithm to ensure smooth transaction processing without any blocking.
