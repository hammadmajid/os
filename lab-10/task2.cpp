#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
bool finished[MAX_PROCESSES];
int num_processes, num_resources;

void printMatrix(int matrix[][MAX_RESOURCES], int rows, int cols, string name) {
    cout << name << ":" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "P" << i << " -> ";
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printAvailable(int avail[], int size) {
    cout << "Available Resources: ";
    for (int i = 0; i < size; i++) {
        cout << avail[i] << " ";
    }
    cout << endl;
}

bool detectDeadlock() {
    memset(finished, false, sizeof(finished));
    int temp_available[MAX_RESOURCES];
    memcpy(temp_available, available, sizeof(available[0]) * num_resources);
    
    bool progress = true;
    
    while (progress) {
        progress = false;
        
        for (int i = 0; i < num_processes; i++) {
            if (finished[i]) continue;
            
            // Check if process i can be satisfied
            bool can_satisfy = true;
            for (int j = 0; j < num_resources; j++) {
                if (request[i][j] > temp_available[j]) {
                    can_satisfy = false;
                    break;
                }
            }
            
            if (can_satisfy) {
                cout << "P" << i << " can complete. Releasing resources: ";
                for (int j = 0; j < num_resources; j++) {
                    cout << allocation[i][j] << " ";
                }
                cout << endl;
                
                // Release resources
                for (int j = 0; j < num_resources; j++) {
                    temp_available[j] += allocation[i][j];
                }
                
                cout << "Updated Available: ";
                for (int j = 0; j < num_resources; j++) {
                    cout << temp_available[j] << " ";
                }
                cout << endl << endl;
                
                finished[i] = true;
                progress = true;
            }
        }
    }
    
    // Check if all processes are finished
    bool all_finished = true;
    for (int i = 0; i < num_processes; i++) {
        if (!finished[i]) {
            all_finished = false;
        }
    }
    
    return all_finished;
}

int main() {
    cout << "Deadlock Detection Algorithm - Task 3" << endl;
    cout << string(70, '=') << endl;
    
    // Task 3: 3 processes, 3 resources
    num_processes = 3;
    num_resources = 3;
    
    // Allocation Matrix
    // P0 → 0 0 1
    // P1 → 1 2 0
    // P2 → 2 0 1
    allocation[0][0] = 0; allocation[0][1] = 0; allocation[0][2] = 1;
    allocation[1][0] = 1; allocation[1][1] = 2; allocation[1][2] = 0;
    allocation[2][0] = 2; allocation[2][1] = 0; allocation[2][2] = 1;
    
    // Request Matrix
    // P0 → 1 0 0
    // P1 → 0 1 1
    // P2 → 1 1 0
    request[0][0] = 1; request[0][1] = 0; request[0][2] = 0;
    request[1][0] = 0; request[1][1] = 1; request[1][2] = 1;
    request[2][0] = 1; request[2][1] = 1; request[2][2] = 0;
    
    // Available Resources: 1 1 0
    available[0] = 1; available[1] = 1; available[2] = 0;
    
    cout << "\nSystem Configuration" << endl;
    cout << string(70, '-') << endl;
    printMatrix(allocation, num_processes, num_resources, "Allocation Matrix");
    cout << endl;
    printMatrix(request, num_processes, num_resources, "Request Matrix");
    cout << endl;
    printAvailable(available, num_resources);
    
    cout << "\n" << string(70, '-') << endl;
    cout << "Deadlock Detection Process (Step by Step):" << endl;
    cout << string(70, '-') << endl;
    cout << "\nStep 1: Check if any process can be satisfied with available resources" << endl;
    cout << "        (Request <= Available for all resources)\n" << endl;
    
    bool is_safe = detectDeadlock();
    
    cout << string(70, '-') << endl;
    cout << "Final Result:" << endl;
    cout << string(70, '-') << endl;
    
    if (is_safe) {
        cout << "System is in SAFE state - No deadlock detected" << endl;
        cout << "Safe Sequence: ";
        for (int i = 0; i < num_processes; i++) {
            if (finished[i]) {
                cout << "P" << i << " ";
            }
        }
        cout << endl;
    } else {
        cout << "System is in DEADLOCK state!" << endl;
        cout << "Deadlocked Processes: ";
        for (int i = 0; i < num_processes; i++) {
            if (!finished[i]) {
                cout << "P" << i << " ";
            }
        }
        cout << endl;
        
        cout << "\nDeadlock Analysis:" << endl;
        cout << "- P0 needs 1 of Resource A (only 0 available initially)" << endl;
        cout << "- P1 needs 1 of Resource C (not available)" << endl;
        cout << "- P2 needs 1 of Resource A and 1 of Resource B" << endl;
        cout << "- Since no process can complete, circular wait exists" << endl;
    }
    
    cout << "\n" << string(70, '=') << endl;
    cout << "Algorithm Summary:" << endl;
    cout << string(70, '=') << endl;
    cout << "The Deadlock Detection Algorithm works as follows:" << endl;
    cout << "1. Check if any process's request can be satisfied" << endl;
    cout << "2. If yes, assume process completes and releases resources" << endl;
    cout << "3. Add released resources to available pool" << endl;
    cout << "4. Repeat until all processes finish (safe) or none can proceed (deadlock)" << endl;
    
    return 0;
}
