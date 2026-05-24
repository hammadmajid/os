#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Parent process created with PID: " << getpid() << endl;

    pid_t pid = fork();

    if (pid < 0) {
        cout << "Fork failed" << endl;
        return 1;
    }
    else if (pid == 0) {
        cout << "Child process started with PID: " << getpid() << endl;
        for (int i = 1; i <= 5; i++) {
            cout << "Child: " << i << endl;
        }
        cout << "Child process finished" << endl;
        exit(0);
    }
    else {
        int status;
        cout << "Parent is waiting for child..." << endl;
        wait(&status);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            cout << "Child process exited with code: " << exit_code << endl;
        }
        cout << "Parent process continuing and now finishing" << endl;
    }

    return 0;
}
