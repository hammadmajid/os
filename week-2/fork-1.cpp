#include <iostream>
#include <unistd.h>     // For fork() and getpid()
#include <sys/types.h>  // For pid_t

using namespace std;

void fork1() {
    int x = 1;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return;
    }

    if (pid == 0) {
        // Child process: increments its own copy of x
        cout << "Child has x = " << ++x << endl;
    } else {
        // Parent process: decrements its own copy of x
        cout << "Parent has x = " << --x << endl;
    }

    // Both processes execute this line
    cout << "Bye from process " << getpid() << " with x = " << x << endl;
}

int main() {
    fork1();
    return 0;
}
