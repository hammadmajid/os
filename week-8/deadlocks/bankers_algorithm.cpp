// g++ -std=c++17 -pthread bankers_algorithm.cpp -o bankers_algorithm

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    const int MAX_PROCESSES = 5;
    const int MAX_RESOURCES = 3;
    
    // Process resource allocations
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1},
        {0, 0, 2}
    };
    
    // Maximum resource demands
    int maxDemand[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    
    // Available resources
    int available[MAX_RESOURCES] = {10, 5, 7};
    
    // Total resources in system
    int totalResources[MAX_RESOURCES] = {10, 5, 7};
    
    cout << "=== BANKER'S ALGORITHM - DEADLOCK AVOIDANCE ===" << endl << endl;
    
    cout << "Initial State:" << endl;
    cout << "Total System Resources: ";
    for (int i = 0; i < MAX_RESOURCES; i++) {
        cout << totalResources[i] << " ";
    }
    cout << endl;
    
    cout << "Available Resources: ";
    for (int i = 0; i < MAX_RESOURCES; i++) {
        cout << available[i] << " ";
    }
    cout << endl;
    
    // Validate: total allocated + available = total resources
    int allocatedSum[MAX_RESOURCES] = {0};
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            allocatedSum[j] += allocation[i][j];
        }
    }
    
    cout << "Currently Allocated: ";
    for (int i = 0; i < MAX_RESOURCES; i++) {
        cout << allocatedSum[i] << " ";
    }
    cout << endl << endl;
    
    // Verify resource conservation
    bool resourceValid = true;
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (allocatedSum[i] + available[i] != totalResources[i]) {
            cout << "ERROR: Resource " << i << " mismatch! (allocated: " << allocatedSum[i]
                 << " + available: " << available[i] << " != total: " << totalResources[i] << ")" << endl;
            resourceValid = false;
        }
    }
    
    if (resourceValid) {
        cout << "✓ Resource validation passed (Allocated + Available = Total)" << endl << endl;
    } else {
        cout << "✗ Resource validation failed!" << endl << endl;
        return 1;
    }
    
    // Calculate need for each process
    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = maxDemand[i][j] - allocation[i][j];
        }
    }
    
    cout << "Need Matrix (Max - Allocated):" << endl;
    cout << "Process\tR0\tR1\tR2" << endl;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        cout << "P" << i << "\t" << need[i][0] << "\t" << need[i][1] 
             << "\t" << need[i][2] << endl;
    }
    cout << endl;
    
    // Safety algorithm
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int safeCount = 0;
    int work[MAX_RESOURCES];
    
    // Initialize work with available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }
    
    cout << "Checking for safe sequence..." << endl;
    
    // Find safe sequence
    for (int iterations = 0; iterations < MAX_PROCESSES; iterations++) {
        bool found = false;
        
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                // Check if process needs can be satisfied
                bool canAllocate = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                
                if (canAllocate) {
                    // Allocate and release
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    
                    finish[i] = true;
                    safeSequence[safeCount++] = i;
                    found = true;
                    cout << "P" << i << " can finish (work now: " 
                         << work[0] << " " << work[1] << " " << work[2] << ")" << endl;
                }
            }
        }
        
        if (!found) break;
    }
    
    cout << endl;
    
    // Check if safe sequence found
    bool systemSafe = (safeCount == MAX_PROCESSES);
    
    if (systemSafe) {
        cout << "SYSTEM IS IN SAFE STATE" << endl;
        cout << "Safe Sequence: ";
        for (int i = 0; i < safeCount; i++) {
            cout << "P" << safeSequence[i] << " ";
        }
        cout << endl;
    } else {
        cout << "SYSTEM IS IN UNSAFE STATE - DEADLOCK POSSIBLE" << endl;
        cout << "Processes that cannot finish: ";
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) cout << "P" << i << " ";
        }
        cout << endl;
    }
    
    return 0;
}
