#include <iostream>

using namespace std;

int main() {
    int marks[5];
    int total = 0;
    double average = 0.0;

    cout << "Enter marks for 5 students:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Student " << (i + 1) << ": ";
        cin >> marks[i];
        total += marks[i];
    }

    average = (double)total / 5;

    cout << "\nAll marks:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Student " << (i + 1) << ": " << marks[i] << endl;
    }

    cout << "\nTotal marks: " << total << endl;
    cout << "Average marks: " << average << endl;

    return 0;
}
