#include <iostream>
using namespace std;

int main() {
    int alloc[3][3] = {
        {0,0,1},
        {1,2,0},
        {2,0,1}
    };

    int req[3][3] = {
        {1,0,0},
        {0,1,1},
        {1,1,0}
    };

    int avail[3] = {1,1,0};
    int work[3] = {1,1,0};
    int finish[3] = {0,0,0};

    int seq[3], idx = 0;

    int changed = 1;

    while(changed) {
        changed = 0;

        for(int i = 0; i < 3; i++) {
            if(!finish[i]) {
                int ok = 1;

                for(int j = 0; j < 3; j++) {
                    if(req[i][j] > work[j]) ok = 0;
                }

                if(ok) {
                    for(int j = 0; j < 3; j++) {
                        work[j] += alloc[i][j];
                    }

                    finish[i] = 1;
                    seq[idx++] = i;
                    changed = 1;
                }
            }
        }
    }

    cout << "Execution order: ";
    for(int i = 0; i < idx; i++) cout << "P" << seq[i] << " ";
    cout << "\n";

    cout << "Final work state: ";
    for(int i = 0; i < 3; i++) cout << work[i] << " ";
    cout << "\n";

    cout << "Deadlocked processes: ";
    int dead = 0;
    for(int i = 0; i < 3; i++) {
        if(!finish[i]) {
            cout << "P" << i << " ";
            dead = 1;
        }
    }

    if(!dead) cout << "None";

    return 0;
}
