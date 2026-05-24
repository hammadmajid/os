#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int balance = 1000;
mutex balanceMutex;

void deposit(int amount, int threadId) {
    balanceMutex.lock();
    cout << "Deposit thread " << threadId << " attempting to deposit: " << amount << endl;
    balance += amount;
    cout << "Deposit thread " << threadId << " deposited " << amount << ", new balance: " << balance << endl;
    balanceMutex.unlock();
}

void withdraw(int amount, int threadId) {
    balanceMutex.lock();
    cout << "Withdrawal thread " << threadId << " attempting to withdraw: " << amount << endl;
    if (balance >= amount) {
        balance -= amount;
        cout << "Withdrawal thread " << threadId << " withdrew " << amount << ", new balance: " << balance << endl;
    } else {
        cout << "Withdrawal thread " << threadId << " - Not enough balance!" << endl;
    }
    balanceMutex.unlock();
}

int main() {
    cout << "Initial balance: " << balance << endl << endl;

    thread d1(deposit, 500, 1);
    thread d2(deposit, 500, 2);
    thread d3(deposit, 500, 3);

    thread w1(withdraw, 300, 1);
    thread w2(withdraw, 300, 2);
    thread w3(withdraw, 300, 3);

    d1.join();
    d2.join();
    d3.join();
    w1.join();
    w2.join();
    w3.join();

    cout << endl << "Final balance: " << balance << endl;

    return 0;
}
