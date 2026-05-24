#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Demonstrating Parent and Child Process Identification..." << endl;
    
    pid_t pid = fork();
    
    if (pid < 0) {
        cout << "Fork failed" << endl;
        return 1;
    }
    else if (pid == 0) {
        // Child process
        cout << "Child Process:" << endl;
        cout << "  Child PID: " << getpid() << endl;
        cout << "  Parent PID (PPID): " << getppid() << endl;
        exit(0);
    }
    else {
        // Parent process
        cout << "Parent Process:" << endl;
        cout << "  Parent PID: " << getpid() << endl;
        cout << "  Child PID returned by fork(): " << pid << endl;
        
        wait(nullptr);
        cout << "Parent: Child process completed" << endl;
    }
    
    return 0;
}
