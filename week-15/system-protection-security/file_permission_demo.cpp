// g++ -std=c++17 file_permission_demo.cpp -o file_permission_demo

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

// Helper to display permissions
void displayPermissions(mode_t mode) {
    cout << ((mode & S_IRUSR) ? "r" : "-");
    cout << ((mode & S_IWUSR) ? "w" : "-");
    cout << ((mode & S_IXUSR) ? "x" : "-");
    cout << ((mode & S_IRGRP) ? "r" : "-");
    cout << ((mode & S_IWGRP) ? "w" : "-");
    cout << ((mode & S_IXGRP) ? "x" : "-");
    cout << ((mode & S_IROTH) ? "r" : "-");
    cout << ((mode & S_IWOTH) ? "w" : "-");
    cout << ((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    const char* testfile = "/tmp/perm_test.txt";
    
    cout << "=== FILE PERMISSION DEMONSTRATION ===" << endl << endl;
    
    // Create test file with specific permissions
    cout << "Creating file with permissions 0644 (rw-r--r--)..." << endl;
    int fd = open(testfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }
    write(fd, "test", 4);
    close(fd);
    
    // Get file status
    struct stat fileStat;
    stat(testfile, &fileStat);
    
    cout << "Original permissions: ";
    displayPermissions(fileStat.st_mode);
    cout << " (0" << oct << (fileStat.st_mode & 0777) << dec << ")" << endl << endl;
    
    // Change permissions
    cout << "Changing to 0755 (rwxr-xr-x)..." << endl;
    chmod(testfile, 0755);
    stat(testfile, &fileStat);
    
    cout << "New permissions: ";
    displayPermissions(fileStat.st_mode);
    cout << " (0" << oct << (fileStat.st_mode & 0777) << dec << ")" << endl << endl;
    
    // Change to read-only
    cout << "Changing to 0444 (r--r--r--)..." << endl;
    chmod(testfile, 0444);
    stat(testfile, &fileStat);
    
    cout << "New permissions: ";
    displayPermissions(fileStat.st_mode);
    cout << " (0" << oct << (fileStat.st_mode & 0777) << dec << ")" << endl << endl;
    
    cout << "Permission bits explanation:" << endl;
    cout << "- Owner: r(4) w(2) x(1)" << endl;
    cout << "- Group: r(4) w(2) x(1)" << endl;
    cout << "- Other: r(4) w(2) x(1)" << endl;
    cout << "Example: 755 = Owner(7=rwx) Group(5=r-x) Other(5=r-x)" << endl;
    
    // Cleanup
    chmod(testfile, 0644);  // Make writable before deleting
    unlink(testfile);
    
    return 0;
}
