#include <iostream>
using namespace std;

int main() {
  int numberOfProcess, i, quantumTime, time = 0, remain;
  int burstTime[20], waitinTime[20], turnAroundTime[20], remainingTime[20]; // rt = remaining time

  cout << "Enter number of processes: ";
  cin >> numberOfProcess;

  cout << "Enter Time Quantum (slice): ";
  cin >> quantumTime;

  // Burst Time Input
  for (i = 0; i < numberOfProcess; i++) {
    cout << "Enter Burst Time for Process " << i << ": ";
    cin >> burstTime[i];
    remainingTime[i] = burstTime[i]; // remaining time mein burst time copy kar diya
    waitinTime[i] = 0;
  }

  remain = numberOfProcess;

  // Round Robin Logic
  while (remain != 0) {
    for (i = 0; i < numberOfProcess; i++) {
      if (remainingTime[i] > 0) {
        if (remainingTime[i] <= quantumTime) // agar remaining time quantum se kam hai
        {
          time = time + remainingTime[i];
          remainingTime[i] = 0;
          turnAroundTime[i] = time;
          remain--;
        } else // agar remaining time quantum se zyada hai
        {
          remainingTime[i] = remainingTime[i] - quantumTime;
          time = time + quantumTime;
        }
      }
    }
  }

  // Waiting Time calculate
  for (i = 0; i < numberOfProcess; i++) {
    waitinTime[i] = turnAroundTime[i] - burstTime[i];
  }

  // Output
  cout << "\n\tProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
  for (i = 0; i < numberOfProcess; i++) {
    cout << "\tP" << i << "\t\t" << burstTime[i] << "\t\t" << waitinTime[i] << "\t\t" << turnAroundTime[i]
         << endl;
  }

  float wtavg = 0, tatavg = 0;
  for (i = 0; i < numberOfProcess; i++) {
    wtavg += waitinTime[i];
    tatavg += turnAroundTime[i];
  }

  cout << "\nAverage Waiting Time     = " << wtavg / numberOfProcess << endl;
  cout << "Average Turnaround Time  = " << tatavg / numberOfProcess << endl;

  return 0;
}
