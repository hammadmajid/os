#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "Child PID: " << getpid() << endl;
        cout << "Parent PID: " << getppid() << endl;
    } else {
        cout << "Parent PID: " << getpid() << endl;
        cout << "Child PID returned by fork(): " << pid << endl;
    }

    return 0;
}
