#include <iostream>
using namespace std;

int main() {
    int alloc1[3][3] = {
        {0,1,0},
        {2,0,0},
        {3,0,3}
    };

    int req1[3][3] = {
        {0,0,0},
        {2,0,2},
        {0,0,0}
    };

    int avail1[3] = {0,0,0};
    int finish1[3] = {0,0,0};
    int work1[3] = {0,0,0};
    for(int i=0;i<3;i++) work1[i]=avail1[i];

    int seq1[3], idx1=0;

    int changed=1;
    while(changed){
        changed=0;
        for(int i=0;i<3;i++){
            if(!finish1[i]){
                int ok=1;
                for(int j=0;j<3;j++){
                    if(req1[i][j]>work1[j]) ok=0;
                }
                if(ok){
                    for(int j=0;j<3;j++) work1[j]+=alloc1[i][j];
                    finish1[i]=1;
                    seq1[idx1++]=i;
                    changed=1;
                }
            }
        }
    }

    cout<<"Task1 Completed: ";
    for(int i=0;i<3;i++){
        if(!finish1[i]) cout<<"P"<<i<<" ";
    }
    cout<<"\nTask1 Safe sequence: ";
    for(int i=0;i<idx1;i++) cout<<"P"<<seq1[i]<<" ";
    cout<<"\n";

    int alloc2[4][3] = {
        {1,0,1},
        {2,1,0},
        {3,0,2},
        {0,1,1}
    };

    int req2[4][3] = {
        {1,1,0},
        {0,1,1},
        {1,0,0},
        {0,0,1}
    };

    int avail2[3] = {1,1,1};
    int finish2[4] = {0,0,0,0};
    int work2[3] = {1,1,1};

    int seq2[4], idx2=0;

    changed=1;
    while(changed){
        changed=0;
        for(int i=0;i<4;i++){
            if(!finish2[i]){
                int ok=1;
                for(int j=0;j<3;j++){
                    if(req2[i][j]>work2[j]) ok=0;
                }
                if(ok){
                    for(int j=0;j<3;j++) work2[j]+=alloc2[i][j];
                    finish2[i]=1;
                    seq2[idx2++]=i;
                    changed=1;
                }
            }
        }
    }

    int dead=0;
    cout<<"Task2 Safe sequence: ";
    for(int i=0;i<idx2;i++) cout<<"P"<<seq2[i]<<" ";
    cout<<"\nTask2 Deadlocked: ";
    for(int i=0;i<4;i++){
        if(!finish2[i]){
            cout<<"P"<<i<<" ";
            dead=1;
        }
    }
    if(!dead) cout<<"None";

    return 0;
}
