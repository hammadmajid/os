// g++ -std=c++17 first_fit_allocation.cpp -o first_fit_allocation

#include <iostream>
using namespace std;

int main() {
    const int MEMORY_SIZE = 100;
    int memory[MEMORY_SIZE];
    
    // Initialize memory (0 = free, process_id = allocated)
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
    
    // Simulate some existing allocations
    for (int i = 0; i < 20; i++) memory[i] = 1;    // Process 1: 0-19
    for (int i = 30; i < 45; i++) memory[i] = 2;   // Process 2: 30-44
    for (int i = 60; i < 75; i++) memory[i] = 3;   // Process 3: 60-74
    
    cout << "=== FIRST-FIT MEMORY ALLOCATION ===" << endl;
    cout << "Memory size: " << MEMORY_SIZE << endl;
    cout << "\nInitial memory state (1,2,3 = allocated, 0 = free):" << endl;
    
    // Show memory
    for (int i = 0; i < MEMORY_SIZE; i += 10) {
        cout << "[" << i << "-" << (i+9) << "]: ";
        for (int j = i; j < i + 10 && j < MEMORY_SIZE; j++) {
            cout << memory[j];
        }
        cout << endl;
    }
    
    // Allocate new process (process 4) with size 15 using first-fit
    int processSize = 15;
    int processId = 4;
    int allocated = 0;
    
    cout << "\nAllocating process " << processId << " (size " << processSize << ") using FIRST-FIT:" << endl;
    
    for (int i = 0; i < MEMORY_SIZE && allocated < processSize; i++) {
        if (memory[i] == 0) {
            memory[i] = processId;
            allocated++;
        } else if (allocated > 0) {
            // Stop if we hit allocated memory
            break;
        }
    }
    
    if (allocated < processSize) {
        cout << "Only " << allocated << " units allocated (fragmentation)" << endl;
    } else {
        cout << "Successfully allocated at first available free space" << endl;
    }
    
    cout << "\nFinal memory state:" << endl;
    for (int i = 0; i < MEMORY_SIZE; i += 10) {
        cout << "[" << i << "-" << (i+9) << "]: ";
        for (int j = i; j < i + 10 && j < MEMORY_SIZE; j++) {
            cout << memory[j];
        }
        cout << endl;
    }
    
    return 0;
}
