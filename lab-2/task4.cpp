#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Creating Multiple Child Processes..." << endl;
    
    // Create first child process
    pid_t pid1 = fork();
    
    if (pid1 < 0) {
        cout << "Fork failed" << endl;
        return 1;
    }
    else if (pid1 == 0) {
        // First child process
        cout << "First Child Process (PID: " << getpid() << ")" << endl;
        exit(0);
    }
    else {
        // Parent: create second child process
        pid_t pid2 = fork();
        
        if (pid2 < 0) {
            cout << "Fork failed" << endl;
            return 1;
        }
        else if (pid2 == 0) {
            // Second child process
            cout << "Second Child Process (PID: " << getpid() << ")" << endl;
            exit(0);
        }
        else {
            // Parent process
            cout << "Parent Process Running (PID: " << getpid() << ")" << endl;
            cout << "First Child PID: " << pid1 << endl;
            cout << "Second Child PID: " << pid2 << endl;
            
            // Wait for both children
            wait(nullptr);
            wait(nullptr);
            cout << "Parent: All child processes completed" << endl;
        }
    }
    
    return 0;
}
