// g++ -std=c++17 mmap_demo.cpp -o mmap_demo

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
using namespace std;

int main() {
    const char* filename = "/tmp/mmap_test.txt";
    const char* content = "This is content for memory mapping demonstration!";
    int fileSize = strlen(content) + 1;
    
    cout << "=== MEMORY-MAPPED FILE DEMONSTRATION ===" << endl << endl;
    
    // Create file and write content
    cout << "Creating file: " << filename << endl;
    int fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }
    
    write(fd, content, fileSize);
    cout << "Wrote " << fileSize << " bytes to file" << endl;
    
    // Memory-map the file
    cout << "\nMemory-mapping file..." << endl;
    char* mmapped = (char*)mmap(nullptr, fileSize, PROT_READ | PROT_WRITE, 
                                 MAP_SHARED, fd, 0);
    
    if (mmapped == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return 1;
    }
    
    cout << "File mapped to virtual memory at address: " << (void*)mmapped << endl;
    
    // Read through memory mapping
    cout << "\nReading through memory mapping:" << endl;
    cout << "Content: " << mmapped << endl;
    
    // Modify through memory mapping
    cout << "\nModifying through memory mapping..." << endl;
    mmapped[0] = 'T';  // Change first char
    mmapped[5] = 'I';
    cout << "Modified content: " << mmapped << endl;
    
    // Unmap
    cout << "\nUnmapping file..." << endl;
    if (munmap(mmapped, fileSize) == -1) {
        perror("munmap failed");
    }
    
    close(fd);
    
    // Cleanup
    unlink(filename);
    cout << "File cleaned up." << endl;
    
    return 0;
}
