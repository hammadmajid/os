#include <iostream>
#include <unistd.h>     // For fork() and getpid()
#include <sys/types.h>  // For pid_t

void fork1() {
    int x = 1;
    pid_t pid = fork();  // Create a new process

    if (pid == -1) {
        // fork failed
        std::cerr << "Fork failed!" << std::endl;
        return;
    }

    if (pid == 0) {
        // Child process
        ++x;  // Increment x in child
        std::cout << "Child has x = " << x << std::endl;
    } else {
        // Parent process
        --x;  // Decrement x in parent
        std::cout << "Parent has x = " << x << std::endl;
    }

    // Runs in both processes
    std::cout << "Bye from process " << getpid()
              << " with x = " << x << std::endl;
}

int main() {
    fork1();
    return 0;
}
