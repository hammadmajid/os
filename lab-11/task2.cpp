#include <iostream>

using namespace std;

int main() {
    int* score = new int;

    cout << "Enter student score: ";
    cin >> *score;

    cout << "Score: " << *score << endl;
    cout << "Memory address: " << score << endl;

    delete score;
    cout << "Memory freed" << endl;

    return 0;
}
