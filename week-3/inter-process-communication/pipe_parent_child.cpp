// g++ -std=c++17 pipe_parent_child.cpp -o pipe_parent_child

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;

int main() {
    int fd[2];
    char message[100];
    const char* parentMsg = "Hello from Parent!";
    const char* childMsg = "Hello from Child!";
    
    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        close(fd[1]);  // Close write end
        
        // Read from pipe
        read(fd[0], message, sizeof(message));
        cout << "Child received: " << message << endl;
        close(fd[0]);
        
    } else if (pid > 0) {
        // Parent process
        close(fd[0]);  // Close read end
        
        // Write to pipe
        write(fd[1], parentMsg, strlen(parentMsg) + 1);
        cout << "Parent sent: " << parentMsg << endl;
        close(fd[1]);
        
        wait(nullptr);
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}
