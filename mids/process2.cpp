#include <unistd.h>     // fork(), execvp()
#include <sys/wait.h>   // wait()
#include <iostream>

using namespace std;

int main() {
    // Create a new process
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "fork failed\n";
        return 1;
    }

    if (pid == 0) {
        // ===== CHILD PROCESS =====

        cout << "Child: going to run 'ls -l'\n";

        // execvp replaces the current program with another program
        // If exec works, NOTHING after this line runs

        // arguments for ls:
        // first arg = program name
        // last must be nullptr
        char* args[] = {
            (char*)"ls",
            (char*)"-l",
            nullptr
        };

        execvp("ls", args);

        // If we reach here → exec FAILED
        cerr << "exec failed\n";
    } else {
        // ===== PARENT PROCESS =====

        cout << "Parent: waiting for child\n";

        // wait for child to finish running "ls"
        wait(nullptr);

        cout << "Child done\n";
    }
}
