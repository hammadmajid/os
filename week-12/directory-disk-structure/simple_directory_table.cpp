// g++ -std=c++17 simple_directory_table.cpp -o simple_directory_table

#include <iostream>
#include <string.h>
using namespace std;

struct DirectoryEntry {
    char filename[32];
    int inode;
    int isUsed;
};

int main() {
    const int MAX_ENTRIES = 10;
    DirectoryEntry directory[MAX_ENTRIES];
    
    // Initialize
    for (int i = 0; i < MAX_ENTRIES; i++) {
        directory[i].isUsed = 0;
    }
    
    cout << "=== SIMPLE DIRECTORY TABLE SIMULATION ===" << endl << endl;
    
    // Add files
    cout << "Adding files to directory..." << endl;
    
    struct {
        const char* name;
        int inode;
    } files[] = {
        {"document.txt", 101},
        {"image.jpg", 102},
        {"program.cpp", 103},
        {"data.csv", 104},
        {"readme.md", 105}
    };
    
    for (int i = 0; i < 5; i++) {
        strcpy(directory[i].filename, files[i].name);
        directory[i].inode = files[i].inode;
        directory[i].isUsed = 1;
        cout << "Added: " << directory[i].filename << " -> inode " << directory[i].inode << endl;
    }
    
    cout << "\nDirectory Table:" << endl;
    cout << "Filename              | Inode | Used" << endl;
    cout << "----------------------|-------|------" << endl;
    
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (directory[i].isUsed) {
            printf("%-21s | %5d | Yes\n", directory[i].filename, directory[i].inode);
        } else {
            printf("%-21s | %5d | No\n", "[Empty]", 0);
        }
    }
    
    // Lookup file
    cout << "\nLooking up 'image.jpg'..." << endl;
    const char* searchName = "image.jpg";
    bool found = false;
    
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (directory[i].isUsed && strcmp(directory[i].filename, searchName) == 0) {
            cout << "Found! Inode: " << directory[i].inode << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "File not found." << endl;
    }
    
    return 0;
}
