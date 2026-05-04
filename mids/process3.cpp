#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cout << "You fucked up\n";
    }


    if (pid == 0) {
        cout << "hi from child\n";
    } else {
        cout << "parent\n";
        
        wait(nullptr); // wait for child go to bed
    }
   

}
