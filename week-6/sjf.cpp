#include <iostream>
using namespace std;

int main() {
  int burstTime[20], waitingTime[20], turnAroundTime[20], i, numberOfProcces;
  float wtavg = 0, tatavg = 0;

  cout << "\nEnter the number of processes: ";
  cin >> numberOfProcces;

  for (i = 0; i < numberOfProcces; i++) {
    cout << "Enter Burst Time for Process " << i << ": ";
    cin >> burstTime[i];
  }

  waitingTime[0] = 0;
  turnAroundTime[0] = burstTime[0];

  for (i = 1; i < numberOfProcces; i++) {
    waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    turnAroundTime[i] = turnAroundTime[i - 1] + burstTime[i];
  }

  for (i = 0; i < numberOfProcces; i++) {
    wtavg += waitingTime[i];
    tatavg += turnAroundTime[i];
  }

  cout << "\n\tPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";

  for (i = 0; i < numberOfProcces; i++) {
    cout << "\tP" << i << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i]
         << endl;
  }

  cout << "\nAverage Waiting Time     : " << wtavg / numberOfProcces << endl;
  cout << "Average Turnaround Time  : " << tatavg / numberOfProcces << endl;

  return 0;
}
