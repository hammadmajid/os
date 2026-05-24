#include <iostream>
#include <thread>

using namespace std;

int matrixA[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int matrixB[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int resultMatrix[3][3];

void addMatrices() {
    cout << "Addition thread started" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    cout << "Addition Result:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void subtractMatrices() {
    cout << "Subtraction thread started" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultMatrix[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    cout << "Subtraction Result:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void multiplyMatrices() {
    cout << "Multiplication thread started" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    cout << "Multiplication Result:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Matrix A:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrixA[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix B:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrixB[i][j] << " ";
        }
        cout << endl;
    }

    thread t1(addMatrices);
    thread t2(subtractMatrices);
    thread t3(multiplyMatrices);

    t1.join();
    t2.join();
    t3.join();

    cout << "All threads completed" << endl;

    return 0;
}
