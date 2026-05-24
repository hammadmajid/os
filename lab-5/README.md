# Lab 5 Implementation of Inter process communication through pipes

Compute the factorial of a number using IPC (Pipe implementation) in C++.
Your program should follow these requirements:
The parent process creates a pipe.
The parent process then forks a child process.
The parent process reads a number from the user and writes it into the pipe.
The child process reads the number from the pipe.
The child process then calculates the factorial of the received number.
Finally, the child process displays the result.
