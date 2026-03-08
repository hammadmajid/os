#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid1 = fork();
    pid_t pid2 = fork();

    if (pid1 == 0 || pid2 == 0) {
        cout << "Child Process PID: " << getpid() << endl;
    } else {
        cout << "Parent Process Running. PID: " << getpid() << endl;
    }

    return 0;
}
