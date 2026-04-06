#include <iostream>
#include <vector>

using namespace std;

// Structure to hold process resource data
struct Process {
    int all[10];   // Allocation
    int max[10];   // Max demand
    int need[10];  // Remaining need
    int flag = 0;  // Finished flag
};

int main() {
    Process f[10];
    int i, j, k, p, b, n, r, g, cnt = 0, id, newr;
    int avail[10], seq[10], fl = 0;

    // Standard C++ input
    cout << "Enter number of processes -- ";
    cin >> n;
    cout << "Enter number of resources -- ";
    cin >> r;

    for (i = 0; i < n; i++) {
        cout << "Enter details for P" << i << endl;
        cout << "Enter allocation -- ";
        for (j = 0; j < r; j++)
            cin >> f[i].all[j];
        
        cout << "Enter Max -- ";
        for (j = 0; j < r; j++)
            cin >> f[i].max[j];
        
        f[i].flag = 0;
    }

    cout << "\nEnter Available Resources -- ";
    for (i = 0; i < r; i++)
        cin >> avail[i];

    // Simulating a New Request
    cout << "\nEnter New Request Details -- " << endl;
    cout << "Enter pid -- ";
    cin >> id;
    cout << "Enter Request for Resources -- ";
    for (i = 0; i < r; i++) {
        cin >> newr;
        f[id].all[i] += newr;
        avail[i] -= newr;
    }

    // Calculating the Need Matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            f[i].need[j] = f[i].max[j] - f[i].all[j];
            if (f[i].need[j] < 0)
                f[i].need[j] = 0;
        }
    }

    // Banker's Algorithm Safety Check
    while (cnt != n) {
        g = 0;
        for (j = 0; j < n; j++) {
            if (f[j].flag == 0) {
                b = 0;
                for (p = 0; p < r; p++) {
                    if (avail[p] >= f[j].need[p])
                        b++;
                    else
                        b--;
                }

                if (b == r) { // If system can satisfy process needs
                    cout << "\nP" << j << " is visited";
                    seq[fl++] = j;
                    f[j].flag = 1;
                    
                    for (k = 0; k < r; k++)
                        avail[k] += f[j].all[k];
                    
                    cnt++;
                    cout << " (Current Avail: ";
                    for (k = 0; k < r; k++)
                        cout << avail[k] << " ";
                    cout << ")";
                    g = 1;
                }
            }
        }

        if (g == 0) {
            cout << "\n\nREQUEST NOT GRANTED -- DEADLOCK OCCURRED";
            cout << "\nSYSTEM IS IN UNSAFE STATE" << endl;
            goto output_table;
        }
    }

    cout << "\n\nSYSTEM IS IN SAFE STATE";
    cout << "\nThe Safe Sequence is -- ( ";
    for (i = 0; i < fl; i++)
        cout << "P" << seq[i] << " ";
    cout << ")" << endl;

output_table:
    cout << "\nProcess\t\tAllocation\tMax\t\tNeed\n";
    for (i = 0; i < n; i++) {
        cout << "P" << i << "\t\t";
        for (j = 0; j < r; j++) cout << f[i].all[j] << " ";
        cout << "\t\t";
        for (j = 0; j < r; j++) cout << f[i].max[j] << " ";
        cout << "\t\t";
        for (j = 0; j < r; j++) cout << f[i].need[j] << " ";
        cout << endl;
    }

    return 0;
}
