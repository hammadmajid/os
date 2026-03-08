#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "Child Process Created" << endl;
    } else if (pid > 0) {
        cout << "Parent Process, Child PID = " << pid << endl;
    } else {
        cout << "Fork Failed" << endl;
    }

    return 0;
}
