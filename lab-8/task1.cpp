#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void printSchedule(Process processes[], int n, string algorithm_name) {
    cout << "\n" << algorithm_name << endl;
    cout << "====================" << endl;
    cout << "Gantt Chart: ";
    for (int i = 0; i < n; i++) {
        cout << "| P" << processes[i].id << " ";
    }
    cout << "|" << endl;
    
    cout << "\nProcess Details:" << endl;
    cout << setw(5) << "PID" << setw(12) << "Arrival" << setw(10) << "Burst" 
         << setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;
    cout << string(54, '-') << endl;
    
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << processes[i].id 
             << setw(12) << processes[i].arrival_time
             << setw(10) << processes[i].burst_time
             << setw(12) << processes[i].waiting_time
             << setw(15) << processes[i].turnaround_time << endl;
        avg_wait += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
    }
    
    cout << string(54, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround / n << endl;
}

void fifo(Process processes[], int n) {
    Process temp[n];
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    
    // Sort by arrival time
    sort(temp, temp + n, [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });
    
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < temp[i].arrival_time) {
            current_time = temp[i].arrival_time;
        }
        current_time += temp[i].burst_time;
        temp[i].completion_time = current_time;
        temp[i].turnaround_time = temp[i].completion_time - temp[i].arrival_time;
        temp[i].waiting_time = temp[i].turnaround_time - temp[i].burst_time;
    }
    
    printSchedule(temp, n, "FIFO (First Come First Serve)");
}

void sjf(Process processes[], int n) {
    Process temp[n];
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    
    int current_time = 0;
    bool scheduled[n] = {false};
    
    for (int i = 0; i < n; i++) {
        int shortest_idx = -1;
        int shortest_burst = INT_MAX;
        
        // Find process with shortest burst time that has arrived
        for (int j = 0; j < n; j++) {
            if (!scheduled[j] && temp[j].arrival_time <= current_time && temp[j].burst_time < shortest_burst) {
                shortest_burst = temp[j].burst_time;
                shortest_idx = j;
            }
        }
        
        // If no process has arrived, jump to next arrival
        if (shortest_idx == -1) {
            for (int j = 0; j < n; j++) {
                if (!scheduled[j] && temp[j].arrival_time > current_time) {
                    current_time = temp[j].arrival_time;
                }
            }
            i--;
            continue;
        }
        
        current_time += temp[shortest_idx].burst_time;
        temp[shortest_idx].completion_time = current_time;
        temp[shortest_idx].turnaround_time = temp[shortest_idx].completion_time - temp[shortest_idx].arrival_time;
        temp[shortest_idx].waiting_time = temp[shortest_idx].turnaround_time - temp[shortest_idx].burst_time;
        scheduled[shortest_idx] = true;
    }
    
    printSchedule(temp, n, "SJF (Shortest Job First)");
}

void round_robin(Process processes[], int n, int time_quantum) {
    Process temp[n];
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    
    int remaining_burst[n];
    for (int i = 0; i < n; i++) remaining_burst[i] = temp[i].burst_time;
    
    int current_time = 0;
    int completed = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0 && temp[i].arrival_time <= current_time) {
                if (remaining_burst[i] <= time_quantum) {
                    current_time += remaining_burst[i];
                    remaining_burst[i] = 0;
                    temp[i].completion_time = current_time;
                    temp[i].turnaround_time = temp[i].completion_time - temp[i].arrival_time;
                    temp[i].waiting_time = temp[i].turnaround_time - temp[i].burst_time;
                    completed++;
                } else {
                    current_time += time_quantum;
                    remaining_burst[i] -= time_quantum;
                }
            }
        }
    }
    
    cout << "\nRound Robin (Time Quantum = " << time_quantum << ")" << endl;
    cout << "====================" << endl;
    cout << "Process Details:" << endl;
    cout << setw(5) << "PID" << setw(12) << "Arrival" << setw(10) << "Burst" 
         << setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;
    cout << string(54, '-') << endl;
    
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << temp[i].id 
             << setw(12) << temp[i].arrival_time
             << setw(10) << temp[i].burst_time
             << setw(12) << temp[i].waiting_time
             << setw(15) << temp[i].turnaround_time << endl;
        avg_wait += temp[i].waiting_time;
        avg_turnaround += temp[i].turnaround_time;
    }
    
    cout << string(54, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround / n << endl;
}

void priority_preemptive(Process processes[], int n) {
    Process temp[n];
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    
    int remaining_burst[n];
    for (int i = 0; i < n; i++) remaining_burst[i] = temp[i].burst_time;
    
    int current_time = 0;
    int completed = 0;
    
    while (completed < n) {
        int highest_priority_idx = -1;
        int highest_priority = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0 && temp[i].arrival_time <= current_time && temp[i].priority < highest_priority) {
                highest_priority = temp[i].priority;
                highest_priority_idx = i;
            }
        }
        
        if (highest_priority_idx == -1) {
            for (int i = 0; i < n; i++) {
                if (remaining_burst[i] > 0 && temp[i].arrival_time > current_time) {
                    current_time = temp[i].arrival_time;
                }
            }
            continue;
        }
        
        current_time++;
        remaining_burst[highest_priority_idx]--;
        
        if (remaining_burst[highest_priority_idx] == 0) {
            temp[highest_priority_idx].completion_time = current_time;
            temp[highest_priority_idx].turnaround_time = temp[highest_priority_idx].completion_time - temp[highest_priority_idx].arrival_time;
            temp[highest_priority_idx].waiting_time = temp[highest_priority_idx].turnaround_time - temp[highest_priority_idx].burst_time;
            completed++;
        }
    }
    
    cout << "\nPPS (Priority Preemptive Scheduling - Lower number = Higher priority)" << endl;
    cout << "====================" << endl;
    cout << "Process Details:" << endl;
    cout << setw(5) << "PID" << setw(12) << "Arrival" << setw(10) << "Burst" 
         << setw(12) << "Priority" << setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;
    cout << string(66, '-') << endl;
    
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << temp[i].id 
             << setw(12) << temp[i].arrival_time
             << setw(10) << temp[i].burst_time
             << setw(12) << temp[i].priority
             << setw(12) << temp[i].waiting_time
             << setw(15) << temp[i].turnaround_time << endl;
        avg_wait += temp[i].waiting_time;
        avg_turnaround += temp[i].turnaround_time;
    }
    
    cout << string(66, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround / n << endl;
}

int main() {
    Process processes[] = {
        {1, 0, 8, 3, 0, 0, 0},
        {2, 1, 4, 2, 0, 0, 0},
        {3, 2, 2, 1, 0, 0, 0},
        {4, 3, 1, 4, 0, 0, 0},
        {5, 4, 5, 2, 0, 0, 0}
    };
    
    int n = 5;
    
    cout << "CPU Scheduling Algorithms Comparison" << endl;
    cout << "====================================" << endl;
    cout << "Processes Input:" << endl;
    cout << setw(5) << "PID" << setw(12) << "Arrival" << setw(10) << "Burst" << setw(12) << "Priority" << endl;
    cout << string(39, '-') << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << processes[i].id 
             << setw(12) << processes[i].arrival_time
             << setw(10) << processes[i].burst_time
             << setw(12) << processes[i].priority << endl;
    }
    
    fifo(processes, n);
    sjf(processes, n);
    round_robin(processes, n, 3);
    priority_preemptive(processes, n);
    
    cout << "\n\nPerformance Analysis:" << endl;
    cout << "====================" << endl;
    cout << "FIFO: Simple, fair, but long average waiting time" << endl;
    cout << "SJF: Minimizes waiting time, but may starve longer jobs" << endl;
    cout << "RR: Fair allocation, good for interactive systems" << endl;
    cout << "PPS: Prioritizes critical tasks, best for real-time systems" << endl;
    
    return 0;
}
