// g++ -std=c++17 system_call_demo.cpp -o system_call_demo

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main() {
    cout << "=== SYSTEM CALL DEMONSTRATION ===" << endl << endl;
    
    // Get process ID of current process
    pid_t myPid = getpid();
    cout << "Current Process ID (PID): " << myPid << endl;
    
    // Get parent process ID
    pid_t parentPid = getppid();
    cout << "Parent Process ID (PPID): " << parentPid << endl;
    
    // Get effective user ID
    uid_t userId = geteuid();
    cout << "Effective User ID (UID): " << userId << endl;
    
    // Get effective group ID
    gid_t groupId = getegid();
    cout << "Effective Group ID (GID): " << groupId << endl;
    
    cout << endl << "=== PROCESS HIERARCHY ===" << endl;
    cout << "This process (PID " << myPid << ") was created by parent (PID " << parentPid << ")" << endl;
    
    return 0;
}
