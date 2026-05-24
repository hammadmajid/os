#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Creating a child process using fork()..." << endl;
    
    pid_t pid = fork();
    
    if (pid < 0) {
        cout << "Fork failed" << endl;
        return 1;
    }
    else if (pid == 0) {
        cout << "This is Child Process" << endl;
        cout << "Child PID: " << getpid() << endl;
        exit(0);
    }
    else {
        cout << "This is Parent Process" << endl;
        cout << "Parent PID: " << getpid() << endl;
        wait(nullptr);
        cout << "Parent: Child process completed" << endl;
    }
    
    return 0;
}
