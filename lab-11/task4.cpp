#include <iostream>

using namespace std;

int main() {
    int salary = 50000;
    int* ptr = &salary;

    cout << "Direct value: " << salary << endl;
    cout << "Address: " << &salary << endl;
    cout << "Value using pointer: " << *ptr << endl;

    return 0;
}
