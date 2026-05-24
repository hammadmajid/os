#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Patient {
    int id;
    int arrival_time;
    int burst_time;  // treatment time
    string priority; // "Critical", "Serious", "Normal"
    int priority_level; // 1 = Critical, 2 = Serious, 3 = Normal
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void printResults(Patient patients[], int n, string algorithm_name) {
    cout << "\n" << algorithm_name << endl;
    cout << string(80, '=') << endl;
    cout << setw(5) << "ID" << setw(12) << "Arrival" << setw(10) << "Burst" 
         << setw(15) << "Priority" << setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;
    cout << string(80, '-') << endl;
    
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << patients[i].id 
             << setw(12) << patients[i].arrival_time
             << setw(10) << patients[i].burst_time
             << setw(15) << patients[i].priority
             << setw(12) << patients[i].waiting_time
             << setw(15) << patients[i].turnaround_time << endl;
        avg_wait += patients[i].waiting_time;
        avg_turnaround += patients[i].turnaround_time;
    }
    
    cout << string(80, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround / n << endl;
}

void fifo(Patient patients[], int n) {
    Patient temp[n];
    for (int i = 0; i < n; i++) temp[i] = patients[i];
    
    sort(temp, temp + n, [](const Patient& a, const Patient& b) {
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
    
    printResults(temp, n, "FIFO Scheduling");
}

void sjf(Patient patients[], int n) {
    Patient temp[n];
    for (int i = 0; i < n; i++) temp[i] = patients[i];
    
    int current_time = 0;
    bool scheduled[n] = {false};
    
    for (int i = 0; i < n; i++) {
        int shortest_idx = -1;
        int shortest_burst = INT_MAX;
        
        for (int j = 0; j < n; j++) {
            if (!scheduled[j] && temp[j].arrival_time <= current_time && temp[j].burst_time < shortest_burst) {
                shortest_burst = temp[j].burst_time;
                shortest_idx = j;
            }
        }
        
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
    
    printResults(temp, n, "SJF Scheduling");
}

void priority_preemptive(Patient patients[], int n) {
    Patient temp[n];
    for (int i = 0; i < n; i++) temp[i] = patients[i];
    
    int remaining_burst[n];
    for (int i = 0; i < n; i++) remaining_burst[i] = temp[i].burst_time;
    
    int current_time = 0;
    int completed = 0;
    
    while (completed < n) {
        int highest_priority_idx = -1;
        int highest_priority = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0 && temp[i].arrival_time <= current_time && temp[i].priority_level < highest_priority) {
                highest_priority = temp[i].priority_level;
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
    
    printResults(temp, n, "Priority Preemptive Scheduling (PPS)");
}

int main() {
    Patient patients[] = {
        {101, 0, 5, "Critical", 1, 0, 0, 0},
        {102, 1, 8, "Serious", 2, 0, 0, 0},
        {103, 2, 3, "Normal", 3, 0, 0, 0},
        {104, 3, 2, "Critical", 1, 0, 0, 0},
        {105, 4, 6, "Serious", 2, 0, 0, 0}
    };
    
    int n = 5;
    
    cout << "Hospital Emergency Unit - CPU Scheduling Comparison" << endl;
    cout << string(80, '=') << endl;
    cout << "\nPatient Data (arrival time, treatment time, priority):" << endl;
    cout << string(80, '-') << endl;
    cout << setw(5) << "ID" << setw(12) << "Arrival" << setw(10) << "Burst" 
         << setw(15) << "Priority" << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << patients[i].id 
             << setw(12) << patients[i].arrival_time
             << setw(10) << patients[i].burst_time
             << setw(15) << patients[i].priority << endl;
    }
    
    fifo(patients, n);
    sjf(patients, n);
    priority_preemptive(patients, n);
    
    cout << "\n" << string(80, '=') << endl;
    cout << "Analysis: Hospital Emergency Unit" << endl;
    cout << string(80, '=') << endl;
    cout << "\nFIFO: Simple but not suitable for emergency - critical patients wait too long" << endl;
    cout << "SJF: Efficient but ignores patient priority - critical patients may wait" << endl;
    cout << "PPS: BEST for Emergency Unit - ensures critical patients are treated first" << endl;
    cout << "\nRecommendation: Use Priority Preemptive Scheduling (PPS)" << endl;
    cout << "- Critical patients get immediate attention (Priority 1)" << endl;
    cout << "- Serious patients are next (Priority 2)" << endl;
    cout << "- Normal patients handled when resources available (Priority 3)" << endl;
    
    return 0;
}
