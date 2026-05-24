#include <iostream>

using namespace std;

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    int* marks = new int[n];

    cout << "Enter marks for " << n << " students:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Student " << (i + 1) << ": ";
        cin >> marks[i];
    }

    cout << "\nAll marks:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Student " << (i + 1) << ": " << marks[i] << endl;
    }

    delete[] marks;
    cout << "\nMemory released" << endl;

    return 0;
}
