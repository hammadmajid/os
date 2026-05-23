// g++ -std=c++17 list_directory.cpp -o list_directory

#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

int main() {
    const char* dirpath = ".";
    
    cout << "=== LISTING DIRECTORY CONTENTS ===" << endl;
    cout << "Directory: " << dirpath << endl << endl;
    
    DIR* dir = opendir(dirpath);
    if (dir == nullptr) {
        perror("opendir failed");
        return 1;
    }
    
    cout << "Contents:" << endl;
    cout << "Name                          | Type" << endl;
    cout << "-------------------------------|----------" << endl;
    
    struct dirent* entry;
    int fileCount = 0, dirCount = 0;
    
    while ((entry = readdir(dir)) != nullptr) {
        // Skip hidden files
        if (entry->d_name[0] == '.') continue;
        
        // Determine type
        const char* type = "Unknown";
        if (entry->d_type == DT_DIR) {
            type = "Directory";
            dirCount++;
        } else if (entry->d_type == DT_REG) {
            type = "File";
            fileCount++;
        }
        
        printf("%-30s | %s\n", entry->d_name, type);
    }
    
    closedir(dir);
    
    cout << "\nSummary:" << endl;
    cout << "Directories: " << dirCount << endl;
    cout << "Files: " << fileCount << endl;
    
    return 0;
}
