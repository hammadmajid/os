#include <unistd.h>     // fork(), getpid(), getppid()
#include <sys/wait.h>   // wait()
#include <iostream>

using namespace std;

int main() {
    // fork() creates a copy of this process
    // After this line, TWO processes exist:
    // - parent (original)
    // - child (copy)
    pid_t pid = fork();

    if (pid < 0) {
        // fork failed
        cerr << "fork failed\n";
        return 1;
    }

    if (pid == 0) {
        // ===== CHILD PROCESS =====
        // pid == 0 means "this is the child"

        // getpid()  → this process ID
        // getppid() → parent process ID
        cout << "Child process\n";
        cout << "My PID: " << getpid() << "\n";
        cout << "My parent PID: " << getppid() << "\n";

        // child exits here
    } else {
        // ===== PARENT PROCESS =====
        // pid > 0 → this is the parent
        // pid value = child's PID

        cout << "Parent process\n";
        cout << "My PID: " << getpid() << "\n";
        cout << "Child PID: " << pid << "\n";

        // wait for child to finish
        // prevents zombie process
        wait(nullptr);

        cout << "Child finished\n";
    }
}
