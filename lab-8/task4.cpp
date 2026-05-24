#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Program {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void analyzeQuantum(int quantum) {
    Program programs[] = {
        {1, 0, 5, 0, 0, 0},
        {2, 1, 8, 0, 0, 0},
        {3, 2, 3, 0, 0, 0},
        {4, 3, 4, 0, 0, 0}
    };
    
    int n = 4;
    int remaining_burst[n];
    for (int i = 0; i < n; i++) remaining_burst[i] = programs[i].burst_time;
    
    int current_time = 0;
    int completed = 0;
    
    cout << "\nTime Quantum = " << quantum << endl;
    cout << string(70, '-') << endl;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0 && programs[i].arrival_time <= current_time) {
                if (remaining_burst[i] <= quantum) {
                    current_time += remaining_burst[i];
                    remaining_burst[i] = 0;
                    programs[i].completion_time = current_time;
                    programs[i].turnaround_time = programs[i].completion_time - programs[i].arrival_time;
                    programs[i].waiting_time = programs[i].turnaround_time - programs[i].burst_time;
                    completed++;
                } else {
                    current_time += quantum;
                    remaining_burst[i] -= quantum;
                }
            }
        }
    }
    
    double avg_wait = 0, avg_turnaround = 0, avg_response = 0;
    
    cout << setw(5) << "PID" << setw(12) << "Arrival" << setw(10) << "Burst" 
         << setw(12) << "Waiting" << setw(15) << "Turnaround" << endl;
    cout << string(70, '-') << endl;
    
    for (int i = 0; i < n; i++) {
        cout << setw(5) << programs[i].id 
             << setw(12) << programs[i].arrival_time
             << setw(10) << programs[i].burst_time
             << setw(12) << programs[i].waiting_time
             << setw(15) << programs[i].turnaround_time << endl;
        avg_wait += programs[i].waiting_time;
        avg_turnaround += programs[i].turnaround_time;
    }
    
    cout << string(70, '-') << endl;
    cout << "Avg Waiting Time: " << fixed << setprecision(2) << avg_wait / n 
         << "  |  Avg Turnaround Time: " << avg_turnaround / n << endl;
}

int main() {
    cout << "University Computer Lab - Round Robin Scheduling Analysis" << endl;
    cout << string(70, '=') << endl;
    cout << "\nProblem: Fairness in CPU allocation with multiple student programs" << endl;
    cout << "Solution: Round Robin scheduling with variable time quantum\n" << endl;
    
    cout << "Program Data:" << endl;
    cout << setw(5) << "PID" << setw(12) << "Arrival" << setw(12) << "Burst Time" << endl;
    cout << string(70, '-') << endl;
    cout << setw(5) << "1" << setw(12) << "0" << setw(12) << "5" << endl;
    cout << setw(5) << "2" << setw(12) << "1" << setw(12) << "8" << endl;
    cout << setw(5) << "3" << setw(12) << "2" << setw(12) << "3" << endl;
    cout << setw(5) << "4" << setw(12) << "3" << setw(12) << "4" << endl;
    
    cout << "\n" << string(70, '=') << endl;
    cout << "Impact of Changing Time Quantum on Performance:" << endl;
    cout << string(70, '=') << endl;
    
    analyzeQuantum(1);
    analyzeQuantum(2);
    analyzeQuantum(3);
    analyzeQuantum(4);
    analyzeQuantum(5);
    
    cout << "\n" << string(70, '=') << endl;
    cout << "Analysis:" << endl;
    cout << string(70, '=') << endl;
    cout << "\nSmaller Quantum (1-2):" << endl;
    cout << "- More context switches (overhead increases)" << endl;
    cout << "- Better fairness and responsiveness" << endl;
    cout << "- Shorter response time per program" << endl;
    
    cout << "\nMedium Quantum (3-4):" << endl;
    cout << "- Balanced overhead and fairness" << endl;
    cout << "- Good average waiting time" << endl;
    cout << "- Reasonable context switch overhead" << endl;
    
    cout << "\nLarger Quantum (5+):" << endl;
    cout << "- Less context switching (lower overhead)" << endl;
    cout << "- Longer waiting times for smaller jobs" << endl;
    cout << "- Approaches FIFO behavior\n" << endl;
    
    cout << "Recommendation: Use quantum = 3" << endl;
    cout << "- Ensures fairness among student programs" << endl;
    cout << "- Minimizes context switch overhead" << endl;
    cout << "- Optimal balance for lab environment" << endl;
    
    return 0;
}
