#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Parent and Child Performing Different Tasks..." << endl;
    
    pid_t pid = fork();
    
    if (pid < 0) {
        cout << "Fork failed" << endl;
        return 1;
    }
    else if (pid == 0) {
        // Child process: print numbers 1 to 5
        cout << "Child Process (PID: " << getpid() << ") - Printing numbers 1 to 5:" << endl;
        for (int i = 1; i <= 5; i++) {
            cout << i << " ";
        }
        cout << endl;
        exit(0);
    }
    else {
        // Parent process: print numbers 6 to 10
        cout << "Parent Process (PID: " << getpid() << ") - Printing numbers 6 to 10:" << endl;
        for (int i = 6; i <= 10; i++) {
            cout << i << " ";
        }
        cout << endl;
        
        wait(nullptr);
        cout << "Parent: Child process completed" << endl;
    }
    
    return 0;
}
