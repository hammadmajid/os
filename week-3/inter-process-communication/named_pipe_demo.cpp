// g++ -std=c++17 named_pipe_demo.cpp -o named_pipe_demo

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int main() {
    const char* fifoPath = "/tmp/demo_fifo";
    const char* message = "Named Pipe Communication Successful!";
    char buffer[100];
    
    // Remove FIFO if it already exists
    unlink(fifoPath);
    
    // Create named pipe (FIFO)
    if (mkfifo(fifoPath, 0666) == -1) {
        perror("mkfifo failed");
        return 1;
    }
    
    cout << "Named pipe created at: " << fifoPath << endl;
    
    // Fork to demonstrate communication
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - reader
        int fd = open(fifoPath, O_RDONLY);
        if (fd == -1) {
            perror("open failed");
            return 1;
        }
        
        read(fd, buffer, sizeof(buffer));
        cout << "Child read from FIFO: " << buffer << endl;
        close(fd);
        
    } else if (pid > 0) {
        // Parent process - writer
        int fd = open(fifoPath, O_WRONLY);
        if (fd == -1) {
            perror("open failed");
            return 1;
        }
        
        write(fd, message, strlen(message) + 1);
        cout << "Parent wrote to FIFO: " << message << endl;
        close(fd);
        
        // Wait for child
        wait(nullptr);
        
        // Clean up FIFO
        unlink(fifoPath);
    }
    
    return 0;
}
