// g++ -std=c++17 -pthread mutex_solution.cpp -o mutex_solution

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

int bankBalance = 1000;
mutex balanceMutex;  // Mutex protects the critical section

void withdraw(int amount, int threadId) {
    // Lock mutex before entering critical section
    balanceMutex.lock();
    
    int temp = bankBalance;
    cout << "Thread " << threadId << " reads balance: " << temp << endl;
    
    this_thread::sleep_for(chrono::microseconds(100));  // Simulate processing
    
    temp = temp - amount;
    bankBalance = temp;
    
    cout << "Thread " << threadId << " withdraws " << amount 
         << ", new balance: " << bankBalance << endl;
    
    // Unlock mutex when leaving critical section
    balanceMutex.unlock();
}

int main() {
    cout << "=== MUTEX SOLUTION ===" << endl;
    cout << "Initial balance: " << bankBalance << endl;
    cout << "Running 3 threads, each withdrawing 200..." << endl;
    cout << "Expected final balance: 400 (1000 - 3*200)" << endl;
    cout << "With mutex, threads execute atomically.\n" << endl;
    
    thread t1(withdraw, 200, 1);
    thread t2(withdraw, 200, 2);
    thread t3(withdraw, 200, 3);
    
    t1.join();
    t2.join();
    t3.join();
    
    cout << "\nFinal balance: " << bankBalance << endl;
    cout << "Balance is correct! Mutex ensures atomic operations." << endl;
    
    return 0;
}
