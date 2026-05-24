#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Order {
    int order_id;
    int arrival_time;
    int prep_time;  // preparation time
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void printSchedule(Order orders[], int n, string algorithm_name) {
    cout << "\n" << algorithm_name << endl;
    cout << string(70, '=') << endl;
    cout << "Gantt Chart: ";
    for (int i = 0; i < n; i++) {
        cout << "| O" << orders[i].order_id << " ";
    }
    cout << "|" << endl;
    
    cout << "\nOrder Details:" << endl;
    cout << setw(8) << "Order ID" << setw(12) << "Arrival" << setw(10) << "Prep Time" 
         << setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;
    cout << string(70, '-') << endl;
    
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(8) << orders[i].order_id 
             << setw(12) << orders[i].arrival_time
             << setw(10) << orders[i].prep_time
             << setw(12) << orders[i].waiting_time
             << setw(15) << orders[i].turnaround_time << endl;
        avg_wait += orders[i].waiting_time;
        avg_turnaround += orders[i].turnaround_time;
    }
    
    cout << string(70, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround / n << endl;
}

void fifo(Order orders[], int n) {
    Order temp[n];
    for (int i = 0; i < n; i++) temp[i] = orders[i];
    
    sort(temp, temp + n, [](const Order& a, const Order& b) {
        return a.arrival_time < b.arrival_time;
    });
    
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < temp[i].arrival_time) {
            current_time = temp[i].arrival_time;
        }
        current_time += temp[i].prep_time;
        temp[i].completion_time = current_time;
        temp[i].turnaround_time = temp[i].completion_time - temp[i].arrival_time;
        temp[i].waiting_time = temp[i].turnaround_time - temp[i].prep_time;
    }
    
    printSchedule(temp, n, "FIFO (First Come First Served)");
}

void sjf(Order orders[], int n) {
    Order temp[n];
    for (int i = 0; i < n; i++) temp[i] = orders[i];
    
    int current_time = 0;
    bool scheduled[n] = {false};
    
    for (int i = 0; i < n; i++) {
        int shortest_idx = -1;
        int shortest_prep = INT_MAX;
        
        for (int j = 0; j < n; j++) {
            if (!scheduled[j] && temp[j].arrival_time <= current_time && temp[j].prep_time < shortest_prep) {
                shortest_prep = temp[j].prep_time;
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
        
        current_time += temp[shortest_idx].prep_time;
        temp[shortest_idx].completion_time = current_time;
        temp[shortest_idx].turnaround_time = temp[shortest_idx].completion_time - temp[shortest_idx].arrival_time;
        temp[shortest_idx].waiting_time = temp[shortest_idx].turnaround_time - temp[shortest_idx].prep_time;
        scheduled[shortest_idx] = true;
    }
    
    printSchedule(temp, n, "SJF (Shortest Job First)");
}

void round_robin(Order orders[], int n, int time_quantum) {
    Order temp[n];
    for (int i = 0; i < n; i++) temp[i] = orders[i];
    
    int remaining_prep[n];
    for (int i = 0; i < n; i++) remaining_prep[i] = temp[i].prep_time;
    
    int current_time = 0;
    int completed = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_prep[i] > 0 && temp[i].arrival_time <= current_time) {
                if (remaining_prep[i] <= time_quantum) {
                    current_time += remaining_prep[i];
                    remaining_prep[i] = 0;
                    temp[i].completion_time = current_time;
                    temp[i].turnaround_time = temp[i].completion_time - temp[i].arrival_time;
                    temp[i].waiting_time = temp[i].turnaround_time - temp[i].prep_time;
                    completed++;
                } else {
                    current_time += time_quantum;
                    remaining_prep[i] -= time_quantum;
                }
            }
        }
    }
    
    cout << "\nRound Robin (Time Quantum = " << time_quantum << ")" << endl;
    cout << string(70, '=') << endl;
    cout << "Order Details:" << endl;
    cout << setw(8) << "Order ID" << setw(12) << "Arrival" << setw(10) << "Prep Time" 
         << setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;
    cout << string(70, '-') << endl;
    
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(8) << temp[i].order_id 
             << setw(12) << temp[i].arrival_time
             << setw(10) << temp[i].prep_time
             << setw(12) << temp[i].waiting_time
             << setw(15) << temp[i].turnaround_time << endl;
        avg_wait += temp[i].waiting_time;
        avg_turnaround += temp[i].turnaround_time;
    }
    
    cout << string(70, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround / n << endl;
}

int main() {
    Order orders[] = {
        {1001, 0, 5, 0, 0, 0},
        {1002, 2, 8, 0, 0, 0},
        {1003, 3, 3, 0, 0, 0},
        {1004, 5, 6, 0, 0, 0},
        {1005, 7, 2, 0, 0, 0}
    };
    
    int n = 5;
    
    cout << "Food Delivery Platform - Order Processing Scheduling" << endl;
    cout << string(70, '=') << endl;
    cout << "\nOrder Input Data:" << endl;
    cout << setw(8) << "Order ID" << setw(12) << "Arrival" << setw(12) << "Prep Time" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(8) << orders[i].order_id 
             << setw(12) << orders[i].arrival_time
             << setw(12) << orders[i].prep_time << endl;
    }
    
    fifo(orders, n);
    sjf(orders, n);
    round_robin(orders, n, 3);
    
    cout << "\n" << string(70, '=') << endl;
    cout << "Analysis and Recommendations:" << endl;
    cout << string(70, '=') << endl;
    cout << "\nFIFO: Fair but may delay quick orders behind slow ones" << endl;
    cout << "SJF: Minimizes waiting time, quick orders prepared first" << endl;
    cout << "RR: Fair distribution of kitchen resources\n" << endl;
    cout << "BEST for Food Delivery: SJF (Shortest Job First)" << endl;
    cout << "- Quick orders delivered faster, improving customer satisfaction" << endl;
    cout << "- Reduces average customer waiting time" << endl;
    cout << "- Better service efficiency with higher order throughput" << endl;
    
    return 0;
}
