#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

// ─── Process Structure ────────────────────────────────────────────────────────

struct Process {
    int   pid;
    string name;
    string type;       // "System" or "User"
    int   priority;    // 1 (highest) → 3 (lowest)
    int   burstTime;
    int   arrivalTime;
    int   remainingTime;
    int   completionTime;
    int   waitingTime;
    int   turnaroundTime;
    int   startTime;
    bool  started;

    Process(int id, string n, string t, int p, int bt, int at)
        : pid(id), name(n), type(t), priority(p),
          burstTime(bt), arrivalTime(at),
          remainingTime(bt), completionTime(0),
          waitingTime(0), turnaroundTime(0),
          startTime(0), started(false) {}
};

// ─── Comparator: lower priority number = higher urgency ──────────────────────

struct ComparePriority {
    bool operator()(const Process* a, const Process* b) {
        if (a->priority != b->priority)
            return a->priority > b->priority;   // min-heap on priority number
        return a->arrivalTime > b->arrivalTime; // FCFS tie-break
    }
};

// ─── Helpers ─────────────────────────────────────────────────────────────────

void printHeader() {
    cout << "\n" << string(72, '=') << "\n";
    cout << "          MULTI-LEVEL QUEUE SCHEDULING SIMULATION\n";
    cout << string(72, '=') << "\n";
}

void printProcessTable(const vector<Process>& processes) {
    cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    cout << "│                        PROCESS TABLE                            │\n";
    cout << "├──────┬────────────┬──────────┬──────────┬───────────┬──────────┤\n";
    cout << "│ PID  │    Name    │   Type   │ Priority │ Burst Time│ Arrival  │\n";
    cout << "├──────┼────────────┼──────────┼──────────┼───────────┼──────────┤\n";
    for (const auto& p : processes) {
        cout << "│ " << setw(4) << p.pid
             << " │ " << setw(10) << left << p.name
             << " │ " << setw(8)  << p.type
             << " │ " << setw(8)  << right << p.priority
             << " │ " << setw(9)  << p.burstTime
             << " │ " << setw(8)  << p.arrivalTime
             << " │\n";
    }
    cout << "└──────┴────────────┴──────────┴──────────┴───────────┴──────────┘\n";
}

void printGanttChart(const vector<pair<int,int>>& gantt,
                     const vector<pair<string,string>>& ganttLabels) {
    cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    cout << "│                         GANTT CHART                             │\n";
    cout << "└─────────────────────────────────────────────────────────────────┘\n";

    // Top border
    cout << " ";
    for (size_t i = 0; i < ganttLabels.size(); i++) cout << "+-------";
    cout << "+\n";

    // Process labels
    cout << " ";
    for (auto& [label, type] : ganttLabels) {
        string display = label.length() > 5 ? label.substr(0,5) : label;
        cout << "| " << setw(5) << left << display << " ";
    }
    cout << "|\n";

    // Type labels (S/U)
    cout << " ";
    for (auto& [label, type] : ganttLabels) {
        cout << "|  (" << type[0] << ")  ";
    }
    cout << "|\n";

    // Bottom border
    cout << " ";
    for (size_t i = 0; i < ganttLabels.size(); i++) cout << "+-------";
    cout << "+\n";

    // Time stamps
    cout << " ";
    for (size_t i = 0; i < gantt.size(); i++) {
        cout << setw(8) << left << gantt[i].first;
    }
    cout << gantt.back().second << "\n";
}

void printResults(const vector<Process>& processes) {
    cout << "\n┌──────────────────────────────────────────────────────────────────────┐\n";
    cout << "│                      SCHEDULING RESULTS                              │\n";
    cout << "├──────┬────────────┬──────────┬────────┬────────┬─────────┬──────────┤\n";
    cout << "│ PID  │    Name    │   Type   │  Start │ Finish │  TAT   │   WT     │\n";
    cout << "├──────┼────────────┼──────────┼────────┼────────┼─────────┼──────────┤\n";

    double totalTAT = 0, totalWT = 0;
    for (const auto& p : processes) {
        cout << "│ " << setw(4)  << right << p.pid
             << " │ " << setw(10) << left  << p.name
             << " │ " << setw(8)  << p.type
             << " │ " << setw(6)  << right << p.startTime
             << " │ " << setw(6)  << p.completionTime
             << " │ " << setw(7)  << p.turnaroundTime
             << " │ " << setw(8)  << p.waitingTime
             << " │\n";
        totalTAT += p.turnaroundTime;
        totalWT  += p.waitingTime;
    }

    int n = processes.size();
    cout << "└──────┴────────────┴──────────┴────────┴────────┴─────────┴──────────┘\n";
    cout << fixed << setprecision(2);
    cout << "\n  Average Turnaround Time : " << totalTAT / n << " ms";
    cout << "\n  Average Waiting Time    : " << totalWT  / n << " ms\n";
}

// ─── Main Scheduler ──────────────────────────────────────────────────────────

void simulate(vector<Process>& processes) {
    // Two multi-level queues
    priority_queue<Process*, vector<Process*>, ComparePriority> systemQueue;
    priority_queue<Process*, vector<Process*>, ComparePriority> userQueue;

    // Gantt chart data
    vector<pair<int,int>>           gantt;       // {start, end}
    vector<pair<string,string>>     ganttLabels; // {name, type}

    int currentTime = 0;
    int completed   = 0;
    int n           = processes.size();

    cout << "\n[Simulation Log]\n" << string(50, '-') << "\n";

    while (completed < n) {
        // Enqueue all processes that have arrived by currentTime
        for (auto& p : processes) {
            if (p.arrivalTime <= currentTime && p.remainingTime == p.burstTime
                && !p.started && p.completionTime == 0) {
                if (p.type == "System")
                    systemQueue.push(&p);
                else
                    userQueue.push(&p);
                cout << "  t=" << setw(3) << currentTime
                     << "  [ARRIVED] " << p.name
                     << " (" << p.type << ", P" << p.priority << ")\n";
                p.started = true; // mark as enqueued
            }
        }

        Process* current = nullptr;

        // System queue has absolute priority over User queue
        if (!systemQueue.empty())
            current = systemQueue.top(), systemQueue.pop();
        else if (!userQueue.empty())
            current = userQueue.top(),  userQueue.pop();

        if (current == nullptr) {
            // CPU idle
            currentTime++;
            continue;
        }

        // Record start time for first execution
        current->startTime = currentTime;

        cout << "  t=" << setw(3) << currentTime
             << "  [RUNNING ] " << current->name
             << " (" << current->type << ", P" << current->priority << ")"
             << "  Burst=" << current->burstTime << "\n";

        // Gantt entry
        gantt.push_back({currentTime, currentTime + current->burstTime});
        ganttLabels.push_back({current->name, current->type});

        // Execute to completion (non-preemptive within queue level)
        currentTime += current->burstTime;
        current->remainingTime = 0;

        // Enqueue any new arrivals during execution
        for (auto& p : processes) {
            if (p.arrivalTime <= currentTime && !p.started
                && p.completionTime == 0) {
                if (p.type == "System")
                    systemQueue.push(&p);
                else
                    userQueue.push(&p);
                cout << "  t=" << setw(3) << p.arrivalTime
                     << "  [ARRIVED] " << p.name
                     << " (" << p.type << ", P" << p.priority
                     << ") [during execution]\n";
                p.started = true;
            }
        }

        current->completionTime  = currentTime;
        current->turnaroundTime  = current->completionTime - current->arrivalTime;
        current->waitingTime     = current->turnaroundTime - current->burstTime;
        completed++;

        cout << "  t=" << setw(3) << currentTime
             << "  [DONE    ] " << current->name
             << "  (TAT=" << current->turnaroundTime
             << ", WT=" << current->waitingTime << ")\n";
    }

    cout << string(50, '-') << "\n";

    printGanttChart(gantt, ganttLabels);
    printResults(processes);
}

// ─── Entry Point ─────────────────────────────────────────────────────────────

int main() {
    printHeader();

    // ── Define processes ──────────────────────────────────────────────────
    //              PID  Name        Type      Pri  Burst  Arrival
    vector<Process> processes = {
        Process(1, "SysInit",   "System",  1,   4,     0),
        Process(2, "MemMgr",    "System",  2,   6,     1),
        Process(3, "DevDrv",    "System",  3,   3,     2),
        Process(4, "Browser",   "User",    1,   8,     0),
        Process(5, "TextEdit",  "User",    2,   5,     3),
        Process(6, "MediaPlay", "User",    3,   7,     4),
        Process(7, "FileSync",  "System",  2,   4,     5),
        Process(8, "Terminal",  "User",    1,   6,     6),
    };

    // Sort by arrival time for clean simulation
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
        return a.arrivalTime < b.arrivalTime;
    });

    printProcessTable(processes);

    cout << "\n  Queue Structure:\n";
    cout << "  ┌─────────────────────────────────────────────────────────┐\n";
    cout << "  │  LEVEL 1 (HIGH)  │  System Queue  │  Priority 1→3       │\n";
    cout << "  │  LEVEL 2 (LOW)   │  User Queue    │  Priority 1→3       │\n";
    cout << "  │  Scheduling      │  Non-preemptive Fixed Priority        │\n";
    cout << "  │  Queue Rule      │  System always executes before User   │\n";
    cout << "  └─────────────────────────────────────────────────────────┘\n";

    simulate(processes);

    cout << "\n" << string(72, '=') << "\n";
    cout << "  Legend: TAT = Turnaround Time  |  WT = Waiting Time  |  (S/U) = System/User\n";
    cout << string(72, '=') << "\n\n";

    return 0;
}
