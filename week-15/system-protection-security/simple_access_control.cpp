// g++ -std=c++17 simple_access_control.cpp -o simple_access_control

#include <iostream>
#include <string.h>
using namespace std;

struct AccessControlEntry {
    char subject[32];     // User or group
    char resource[32];    // File or resource
    int canRead;
    int canWrite;
    int canExecute;
};

int main() {
    const int MAX_ACL = 10;
    AccessControlEntry acl[MAX_ACL];
    int aclSize = 0;
    
    cout << "=== SIMPLE ACCESS CONTROL LIST (ACL) ===" << endl << endl;
    
    // Define some access rules
    cout << "Defining access control policies..." << endl << endl;
    
    struct {
        const char* subject;
        const char* resource;
        int read, write, execute;
    } policies[] = {
        {"alice", "document.txt", 1, 1, 0},
        {"bob", "document.txt", 1, 0, 0},
        {"alice", "script.sh", 1, 1, 1},
        {"charlie", "script.sh", 0, 0, 0},
        {"bob", "data.csv", 1, 1, 0}
    };
    
    // Load ACL
    for (int i = 0; i < 5; i++) {
        strcpy(acl[aclSize].subject, policies[i].subject);
        strcpy(acl[aclSize].resource, policies[i].resource);
        acl[aclSize].canRead = policies[i].read;
        acl[aclSize].canWrite = policies[i].write;
        acl[aclSize].canExecute = policies[i].execute;
        aclSize++;
    }
    
    cout << "ACL Table:" << endl;
    cout << "User     | Resource      | Read | Write | Execute" << endl;
    cout << "---------|---------------|------|-------|--------" << endl;
    
    for (int i = 0; i < aclSize; i++) {
        printf("%-8s | %-13s | %s    | %s     | %s\n",
               acl[i].subject,
               acl[i].resource,
               acl[i].canRead ? "Yes" : "No",
               acl[i].canWrite ? "Yes" : "No",
               acl[i].canExecute ? "Yes" : "No");
    }
    
    cout << "\nAccess Control Checks:" << endl;
    cout << "---------------------" << endl;
    
    // Check permissions
    struct {
        const char* user;
        const char* resource;
        const char* operation;
    } checks[] = {
        {"alice", "document.txt", "read"},
        {"bob", "document.txt", "write"},
        {"alice", "script.sh", "execute"},
        {"charlie", "script.sh", "read"}
    };
    
    for (int i = 0; i < 4; i++) {
        bool allowed = false;
        
        for (int j = 0; j < aclSize; j++) {
            if (strcmp(acl[j].subject, checks[i].user) == 0 &&
                strcmp(acl[j].resource, checks[i].resource) == 0) {
                
                if (strcmp(checks[i].operation, "read") == 0) {
                    allowed = acl[j].canRead;
                } else if (strcmp(checks[i].operation, "write") == 0) {
                    allowed = acl[j].canWrite;
                } else if (strcmp(checks[i].operation, "execute") == 0) {
                    allowed = acl[j].canExecute;
                }
                break;
            }
        }
        
        cout << checks[i].user << " " << checks[i].operation << " "
             << checks[i].resource << ": "
             << (allowed ? "ALLOWED" : "DENIED") << endl;
    }
    
    return 0;
}
