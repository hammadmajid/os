// g++ -std=c++17 file_read_write.cpp -o file_read_write

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
using namespace std;

int main() {
    const char* filename = "/tmp/test_file.txt";
    const char* content = "Hello from file I/O!\nThis is line 2.\nThis is line 3.";
    char buffer[256];
    
    cout << "=== FILE I/O DEMONSTRATION ===" << endl << endl;
    
    // Create and write to file
    cout << "Creating file: " << filename << endl;
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }
    
    int written = write(fd, content, strlen(content));
    cout << "Wrote " << written << " bytes" << endl;
    close(fd);
    
    // Read from file
    cout << "\nReading file:" << endl;
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }
    
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';
    
    cout << "Read " << bytesRead << " bytes:" << endl;
    cout << buffer << endl;
    
    close(fd);
    
    // Append to file
    cout << "\nAppending to file..." << endl;
    fd = open(filename, O_APPEND | O_WRONLY);
    const char* appendedContent = "\nAppended line.";
    write(fd, appendedContent, strlen(appendedContent));
    close(fd);
    
    // Read again
    cout << "Reading file after append:" << endl;
    fd = open(filename, O_RDONLY);
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';
    cout << buffer << endl;
    close(fd);
    
    // Cleanup
    unlink(filename);
    cout << "\nFile cleaned up." << endl;
    
    return 0;
}
