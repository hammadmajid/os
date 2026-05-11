#include <iostream>
using namespace std;

int main() {
    // Number of processes and resource types
    int numProcesses = 3, numResourceTypes = 3;

    /**
     * Allocation Matrix: Shows how many resources of each type each process has already allocated
     * Row = Process, Column = Resource Type
     * Process 0: [0, 1, 0] - has 1 unit of resource type 1
     * Process 1: [2, 0, 0] - has 2 units of resource type 0
     * Process 2: [3, 0, 3] - has 3 units of resource types 0 and 2
     */
    int allocation[3][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3}
    };

    /**
     * Request Matrix: Shows how many additional resources each process is requesting
     * Row = Process, Column = Resource Type
     * Process 0: [0, 0, 0] - requesting nothing
     * Process 1: [2, 0, 2] - requesting 2 more of resource types 0 and 2
     * Process 2: [0, 0, 0] - requesting nothing
     */
    int request[3][3] = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0}
    };

    // Available resources: initially no resources available
    int available[3] = {0, 0, 0};
    
    // Track which processes have finished execution
    int finish[3] = {0, 0, 0};

    /**
     * Banker's Algorithm - Safety Check
     * Iterates through processes and tries to find a safe sequence
     * If a process's resource requests can be satisfied by available resources,
     * it runs to completion and releases all its allocated resources
     */
    for(int i = 0; i < numProcesses; i++) {
        // Skip processes that have already finished
        if(!finish[i]) {
            bool canProcessRun = true;

            // Check if this process's requests can be satisfied
            for(int j = 0; j < numResourceTypes; j++) {
                if(request[i][j] > available[j]) {
                    canProcessRun = false;
                    break;
                }
            }

            // If resources are available, process runs and releases its allocation
            if(canProcessRun) {
                // Add the process's allocated resources back to available pool
                // (This simulates the process completing and releasing resources)
                for(int j = 0; j < numResourceTypes; j++) {
                    available[j] += allocation[i][j];
                }

                // Mark process as finished
                finish[i] = 1;
                cout << "P" << i << " finished\n";
                
                // Restart from beginning to check other processes with new available resources
                i = -1;
            }
        }
    }

    // Check for deadlocked processes (those that never finished)
    cout << "\nDeadlocked Processes: ";
    bool deadlockExists = false;

    for(int i = 0; i < numProcesses; i++) {
        if(!finish[i]) {
            cout << "P" << i << " ";
            deadlockExists = true;
        }
    }

    // Print result
    if(!deadlockExists)
        cout << "None";

    return 0;
}
