#include <iostream>
using namespace std;

int main()
{
    int n, i, j;
    int bt[20], priority[20], wt[20], tat[20];
    float wtavg = 0, tatavg = 0;
    int temp;                          // FIX 1: added missing semicolon

    // FIX 2: read number of processes (was never inputted)
    cout << "Enter Number of Processes: ";
    cin >> n;

    // FIX 3: added missing burst time input inside the loop
    for(i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for Process " << i << ": ";
        cin >> bt[i];
        cout << "Enter Priority for Process " << i << " (Lower Number = Higher Priority): ";
        cin >> priority[i];
    }

    // Sorting according to Priority (Bubble Sort)
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(priority[i] > priority[j])   // Lower priority number = higher priority
            {
                // Swap Priority
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // Swap Burst Time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    wt[0] = 0;
    tat[0] = bt[0];
    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = wt[i] + bt[i];
    }

    for(i = 0; i < n; i++)
    {
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // FIX 4: added missing output section
    cout << "\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for(i = 0; i < n; i++)
    {
        cout << "P" << i << "\t" << bt[i] << "\t\t" << priority[i]
             << "\t\t" << wt[i] << "\t\t" << tat[i] << "\n";
    }

    cout << "\nAverage Waiting Time:    " << wtavg / n;
    cout << "\nAverage Turnaround Time: " << tatavg / n << "\n";

    return 0;
}   // FIX 5: added missing closing brace for main()
