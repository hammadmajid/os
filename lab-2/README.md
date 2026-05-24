# Lab 2

##  Task 1: Create a Child Process

Scenario:
Write a program that creates a child process
using fork(). Both parent and child should print their Process ID (PID).
Task Requirements:
   Create a process using fork().
 If the process is child, print 'This is Child
Process' and its PID.
If the process is parent, print 'This is
Parent Process' and its PID.

Lab Task 2: Identify Parent and Child Process
Scenario:
Develop a program to demonstrate the
difference between parent and child processes.
Task Requirements:
Use fork() to create a new process.
The child process should display its PID and
Parent PID (PPID).
The parent process should display its PID and
the Child PID returned by fork().

## Task 3: Parent and Child Performing Different Tasks

Scenario:
Create a program where parent and child
processes perform different operations.
Task Requirements:
Create a child process using fork().
The child process should print numbers from 1
to 5.
The parent process should print numbers from
6 to 10.
Lab Task 4: Multiple Child Processes
Scenario:
Write a program that creates two child
processes using fork().
Task Requirements:
Use fork() twice to create processes.
Each child process should print its PID.
The parent process should print 'Parent
Process Running' along with its PID.
Lab Task 5: Demonstrate fork() Return Values
Scenario:
Develop a program to observe the return
values of fork().
Task Requirements:
Call fork() and store the return value in a
variable.
If the value is 0, print 'Child Process
Created'.
If the value is greater than 0, print 'Parent
Process, Child PID = ____'.
If the value is less than 0, print 'Fork
Failed'.
