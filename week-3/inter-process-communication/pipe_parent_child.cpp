// g++ -std=c++17 pipe_parent_child.cpp -o pipe_parent_child

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;

int main() {
    int fd[2];      // Parent to child pipe
    int fd2[2];     // Child to parent pipe
    char message[100];
    const char* parentMsg = "Hello from Parent!";
    const char* childMsg = "Hello from Child!";
    
    // Create pipes
    if (pipe(fd) == -1 || pipe(fd2) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        close(fd[1]);   // Close write end of parent->child pipe
        close(fd2[0]);  // Close read end of child->parent pipe
        
        // Read from parent
        read(fd[0], message, sizeof(message));
        cout << "Child received: " << message << endl;
        close(fd[0]);
        
        // Send message to parent
        write(fd2[1], childMsg, strlen(childMsg) + 1);
        cout << "Child sent: " << childMsg << endl;
        close(fd2[1]);
        
    } else if (pid > 0) {
        // Parent process
        close(fd[0]);   // Close read end of parent->child pipe
        close(fd2[1]);  // Close write end of child->parent pipe
        
        // Write to child
        write(fd[1], parentMsg, strlen(parentMsg) + 1);
        cout << "Parent sent: " << parentMsg << endl;
        close(fd[1]);
        
        // Read from child
        read(fd2[0], message, sizeof(message));
        cout << "Parent received: " << message << endl;
        close(fd2[0]);
        
        wait(nullptr);
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}
