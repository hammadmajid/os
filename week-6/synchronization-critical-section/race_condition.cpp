// g++ -std=c++17 -pthread race_condition.cpp -o race_condition

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int bankBalance = 1000;  // Shared account balance

void withdraw(int amount, int threadId) {
    // UNSAFE: No synchronization on shared resource
    int temp = bankBalance;
    cout << "Thread " << threadId << " reads balance: " << temp << endl;
    
    this_thread::sleep_for(chrono::microseconds(100));  // Simulate processing
    
    temp = temp - amount;
    bankBalance = temp;
    
    cout << "Thread " << threadId << " withdraws " << amount 
         << ", new balance: " << bankBalance << endl;
}

int main() {
    cout << "=== RACE CONDITION EXAMPLE ===" << endl;
    cout << "Initial balance: " << bankBalance << endl;
    cout << "Running 3 threads, each withdrawing 200..." << endl;
    cout << "Expected final balance: 400 (1000 - 3*200)" << endl;
    cout << "Actual balance will likely be different due to race conditions!\n" << endl;
    
    thread t1(withdraw, 200, 1);
    thread t2(withdraw, 200, 2);
    thread t3(withdraw, 200, 3);
    
    t1.join();
    t2.join();
    t3.join();
    
    cout << "\nFinal balance: " << bankBalance << endl;
    cout << "Notice: Balance is incorrect due to interleaved execution!" << endl;
    
    return 0;
}
