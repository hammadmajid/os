#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Parent process created with PID: " << getpid() << endl;

    for (int i = 1; i <= 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            cout << "Fork failed" << endl;
            return 1;
        }
        else if (pid == 0) {
            cout << "Child " << i << " created with PID: " << getpid() << endl;
            exit(i);
        }
    }

    cout << "Parent is waiting for all children..." << endl;

    for (int i = 1; i <= 3; i++) {
        int status;
        pid_t child_pid = wait(&status);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            cout << "Child with PID " << child_pid << " finished with exit code: " << exit_code << endl;
        }
    }

    cout << "All child processes have finished successfully" << endl;

    return 0;
}
