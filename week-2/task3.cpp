#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        for (int i = 1; i <= 5; i++) {
            cout << i << endl;
        }
    } else {
        for (int i = 6; i <= 10; i++) {
            cout << i << endl;
        }
    }

    return 0;
}
