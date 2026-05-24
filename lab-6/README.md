# Lab 6 implementation of Multithreading

## Task 1
Write a program for matrix addition, subtraction and multiplication using multithreading.

## Task 2

Write a C++ program that performs matrix addition, subtraction and multiplication using multithreading. Each operation must run in a separate thread. You will use a 3x3 matrix for all operations. After each thread finishes its operation it should print the result on screen. You must use thread.join() to wait for all threads to finish before program ends.  Use the following two matrices for your program. Matrix A should be {1,2,3}, {4,5,6}, {7,8,9} and Matrix B should be {9,8,7}, {6,5,4}, {3,2,1}. Your program should create three threads, one for addition, one for subtraction and one for multiplication. Each thread should print its result separately after it finishes. Make sure all three threads run at the same time and not one after another.

## Lab task 3
Write a C++ program that simulates a bank account where multiple people are depositing and withdrawing money at the same time using threads. You must use mutex lock to prevent any errors in the shared balance. The shared balance variable should start at 1000. You will create three deposit threads where each thread deposits 500 into the account. You will also create three withdrawal threads where each thread withdraws 300 from the account. After every deposit and withdrawal the current balance should be printed on screen.
You must use lock() and unlock() to protect the balance variable so that two threads do not change it at the same time. Withdrawal should only happen if there is enough balance in the account. If balance is not enough then print a message saying "Not enough balance!" At the end of the program print the final balance. As a bonus challenge for fast students, add a third thread that checks the balance every second and prints a warning if balance goes below 500.
