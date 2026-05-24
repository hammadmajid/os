// g++ -std=c++17 fcfs_process_scheduling.cpp -o fcfs_process_scheduling

#include <iostream>
using namespace std;

int main() {
    // Fixed process data - demonstrating FCFS with realistic example
    int burstTime[5] = {8, 4, 2, 1, 3};
    int waitingTime[5] = {0};
    int turnaroundTime[5] = {0};
    int numProcesses = 5;
    
    // Calculate waiting and turnaround times
    // First process has no waiting time
    waitingTime[0] = 0;
    turnaroundTime[0] = burstTime[0];
    
    // For remaining processes, waiting time = sum of all previous burst times
    for (int i = 1; i < numProcesses; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }
    
    // Display results
    cout << "\n=== FIRST-COME-FIRST-SERVED (FCFS) SCHEDULING ===" << endl;
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    cout << "-------\t----------\t------------\t---------------" << endl;
    
    float avgWaiting = 0, avgTurnaround = 0;
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i << "\t" << burstTime[i] << "\t\t" 
             << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
        avgWaiting += waitingTime[i];
        avgTurnaround += turnaroundTime[i];
    }
    
    avgWaiting /= numProcesses;
    avgTurnaround /= numProcesses;
    
    cout << "\nAverage Waiting Time: " << avgWaiting << endl;
    cout << "Average Turnaround Time: " << avgTurnaround << endl;
    
    return 0;
}
