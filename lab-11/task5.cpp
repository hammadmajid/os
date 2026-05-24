#include <iostream>

using namespace std;

int main() {
    int oldSize = 3;
    int newSize = 5;

    int* oldArray = new int[oldSize];

    cout << "Enter book IDs for " << oldSize << " books:" << endl;
    for (int i = 0; i < oldSize; i++) {
        cout << "Book " << (i + 1) << ": ";
        cin >> oldArray[i];
    }

    cout << "\nOriginal array:" << endl;
    for (int i = 0; i < oldSize; i++) {
        cout << "Book " << (i + 1) << ": " << oldArray[i] << endl;
    }

    int* newArray = new int[newSize];

    for (int i = 0; i < oldSize; i++) {
        newArray[i] = oldArray[i];
    }

    delete[] oldArray;

    cout << "\nEnter book IDs for " << (newSize - oldSize) << " new books:" << endl;
    for (int i = oldSize; i < newSize; i++) {
        cout << "Book " << (i + 1) << ": ";
        cin >> newArray[i];
    }

    cout << "\nUpdated array:" << endl;
    for (int i = 0; i < newSize; i++) {
        cout << "Book " << (i + 1) << ": " << newArray[i] << endl;
    }

    delete[] newArray;
    cout << "\nMemory released" << endl;

    return 0;
}
