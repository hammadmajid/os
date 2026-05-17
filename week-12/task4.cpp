#include <iostream>
using namespace std;

int main() 
{ 
    int found, flag, l;
    int p[10][10], c[10][10];
    int tp, tr, i, j, k = 1;
    int m[10], r[10], a[10], temp[10];
    int sum = 0;

    cout << "Enter total no of processes: ";
    cin >> tp;

    cout << "Enter total no of resources: ";
    cin >> tr;

    cout << "Enter claim (Max Need) matrix:\n";
    for(i = 1; i <= tp; i++) 
    { 
        cout << "Process " << i << ":\n";
        for(j = 1; j <= tr; j++) 
            cin >> c[i][j];
    } 

    cout << "Enter allocation matrix:\n";
    for(i = 1; i <= tp; i++) 
    { 
        cout << "Process " << i << ":\n";
        for(j = 1; j <= tr; j++) 
            cin >> p[i][j];
    }

    cout << "Enter resource vector (Total resources):\n";
    for(i = 1; i <= tr; i++) 
        cin >> r[i];

    cout << "Enter availability vector (Available resources):\n";
    for(i = 1; i <= tr; i++) 
    { 
        cin >> a[i]; 
        temp[i] = a[i];
    }

    // Step 1: find processes with zero allocation
    for(i = 1; i <= tp; i++)
    { 
        sum = 0; 
        for(j = 1; j <= tr; j++) 
            sum += p[i][j]; 
        
        if(sum == 0) 
        { 
            m[k] = i; 
            k++;
        } 
    }

    // Step 2: check remaining processes
    for(i = 1; i <= tp; i++) 
    { 
        flag = 1;
        for(l = 1; l < k; l++) 
        {
            if(i == m[l]) 
                flag = 0;
        }

        if(flag == 1)
        {
            for(j = 1; j <= tr; j++) 
            {
                if(c[i][j] > temp[j]) 
                {
                    flag = 0; 
                    break;
                }
            }
        }

        if(flag == 1) 
        {
            m[k] = i; 
            k++; 
            for(j = 1; j <= tr; j++) 
                temp[j] += p[i][j];
        }
    }

    cout << "Deadlock causing processes are: ";
    for(j = 1; j <= tp; j++) 
    { 
        found = 0; 
        for(i = 1; i < k; i++) 
        { 
            if(j == m[i]) 
                found = 1;
        }
        if(found == 0) 
            cout << "P" << j << " ";
    }

    return 0;
}
