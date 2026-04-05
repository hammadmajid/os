#include <iostream>
using namespace std;

int main() {
  int burstTime[20], waitingTime[20], turnaroundTime[20],  numberOfProcess;
  float waitingTimeAverage = 0, turnaroundTimeAverage = 0;

  cout << "\nEnter the number of processes: ";
  cin >> numberOfProcess;

  for (int i = 0; i < numberOfProcess; i++) {
    cout << "Enter Burst Time for Process " << i << ": ";
    cin >> burstTime[i];
  }

  waitingTime[0] = 0;
  turnaroundTime[0] = burstTime[0];

  for (int i = 1; i < numberOfProcess; i++) {
    waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    turnaroundTime[i] = turnaroundTime[i - 1] + burstTime[i];
  }

  for (int i = 0; i < numberOfProcess; i++) {
    waitingTimeAverage += waitingTime[i];
    turnaroundTimeAverage += turnaroundTime[i];
  }

  cout << "\n\tPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";

  for (int i = 0; i < numberOfProcess; i++) {
    cout << "\tP" << i << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i]
         << endl;
  }

  cout << "\nAverage Waiting Time     : " << waitingTimeAverage / numberOfProcess << endl;
  cout << "Average Turnaround Time  : " << turnaroundTimeAverage / numberOfProcess << endl;

  return 0;
}
