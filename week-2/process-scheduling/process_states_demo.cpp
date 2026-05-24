// g++ -std=c++17 process_states_demo.cpp -o process_states_demo

#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "This is Child Process. PID: " << getpid() << endl;
    } else {
        cout << "This is Parent Process. PID: " << getpid() << endl;
    }

    return 0;
}
