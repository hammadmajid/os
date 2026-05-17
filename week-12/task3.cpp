#include <iostream>
using namespace std;

int main() {
    int numProcesses = 3, numResourceTypes = 3;

    int allocation[3][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3}
    };

    int request[3][3] = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0}
    };

    int available[3] = {0, 0, 0};
    
    int finish[3] = {0, 0, 0};

    for(int i = 0; i < numProcesses; i++) {
        if(!finish[i]) {
            bool canProcessRun = true;
            for(int j = 0; j < numResourceTypes; j++) {
                if(request[i][j] > available[j]) {
                    canProcessRun = false;
                    break;
                }
            }

            if(canProcessRun) {
                for(int j = 0; j < numResourceTypes; j++) {
                    available[j] += allocation[i][j];
                }

                finish[i] = 1;
                cout << "P" << i << " finished\n";
                
                i = -1;
            }
        }
    }

    cout << "\nDeadlocked Processes: ";
    bool deadlockExists = false;

    for(int i = 0; i < numProcesses; i++) {
        if(!finish[i]) {
            cout << "P" << i << " ";
            deadlockExists = true;
        }
    }

    if(!deadlockExists)
        cout << "None";

    return 0;
}
