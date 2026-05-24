#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Demonstrating fork() Return Values..." << endl;
    
    pid_t pid = fork();
    
    if (pid < 0) {
        cout << "Fork Failed" << endl;
        return 1;
    }
    else if (pid == 0) {
        cout << "Child Process Created" << endl;
        cout << "Child PID: " << getpid() << endl;
        exit(0);
    }
    else {
        cout << "Parent Process, Child PID = " << pid << endl;
        cout << "Parent PID: " << getpid() << endl;
        
        wait(nullptr);
        cout << "Parent: Child process completed" << endl;
    }
    
    return 0;
}
