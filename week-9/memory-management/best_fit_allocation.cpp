// g++ -std=c++17 best_fit_allocation.cpp -o best_fit_allocation

#include <iostream>
#include <climits>
using namespace std;

int main() {
    const int MEMORY_SIZE = 100;
    int memory[MEMORY_SIZE];
    
    // Initialize memory (0 = free, process_id = allocated)
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
    
    // Simulate existing allocations
    for (int i = 0; i < 20; i++) memory[i] = 1;     // Process 1: 0-19
    for (int i = 30; i < 45; i++) memory[i] = 2;    // Process 2: 30-44
    for (int i = 60; i < 75; i++) memory[i] = 3;    // Process 3: 60-74
    
    cout << "=== BEST-FIT MEMORY ALLOCATION ===" << endl;
    cout << "Memory size: " << MEMORY_SIZE << endl;
    cout << "\nInitial memory state:" << endl;
    
    // Show memory
    for (int i = 0; i < MEMORY_SIZE; i += 10) {
        cout << "[" << i << "-" << (i+9) << "]: ";
        for (int j = i; j < i + 10 && j < MEMORY_SIZE; j++) {
            cout << memory[j];
        }
        cout << endl;
    }
    
    // Find best-fit hole for process 4 (size 15)
    int processSize = 15;
    int processId = 4;
    int bestStart = -1;
    int bestSize = INT_MAX;
    int currentHoleStart = -1;
    int currentHoleSize = 0;
    
    // Find all holes
    cout << "\nFinding holes..." << endl;
    for (int i = 0; i <= MEMORY_SIZE; i++) {
        if (i < MEMORY_SIZE && memory[i] == 0) {
            if (currentHoleStart == -1) {
                currentHoleStart = i;
                currentHoleSize = 0;
            }
            currentHoleSize++;
        } else {
            if (currentHoleStart != -1) {
                cout << "Hole at [" << currentHoleStart << "-" << (currentHoleStart + currentHoleSize - 1) 
                     << "] size: " << currentHoleSize << endl;
                
                // Check if this hole is suitable and better than current best
                if (currentHoleSize >= processSize && currentHoleSize < bestSize) {
                    bestStart = currentHoleStart;
                    bestSize = currentHoleSize;
                }
                
                currentHoleStart = -1;
                currentHoleSize = 0;
            }
        }
    }
    
    // Allocate in best-fit hole
    if (bestStart != -1) {
        cout << "\nBest-fit hole: [" << bestStart << "-" << (bestStart + bestSize - 1) 
             << "] size: " << bestSize << endl;
        cout << "Allocating process " << processId << " (size " << processSize << ") in best-fit hole" << endl;
        
        for (int i = bestStart; i < bestStart + processSize; i++) {
            memory[i] = processId;
        }
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
