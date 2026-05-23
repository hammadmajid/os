// g++ -std=c++17 -pthread thread_shared_data_problem.cpp -o thread_shared_data_problem

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int sharedCounter = 0;  // Shared resource without synchronization

void incrementCounter(int iterations) {
    for (int i = 0; i < iterations; i++) {
        // Race condition: multiple threads modify simultaneously
        int temp = sharedCounter;
        
        // Simulate some work
        this_thread::sleep_for(chrono::microseconds(1));
        
        sharedCounter = temp + 1;
    }
}

int main() {
    cout << "=== RACE CONDITION DEMONSTRATION ===" << endl;
    cout << "Initial counter value: " << sharedCounter << endl;
    cout << "Starting 4 threads, each incrementing 250 times..." << endl;
    
    // Create 4 threads, each incrementing 250 times
    // Expected result: 1000, but due to race condition, it will be less
    thread t1(incrementCounter, 250);
    thread t2(incrementCounter, 250);
    thread t3(incrementCounter, 250);
    thread t4(incrementCounter, 250);
    
    // Wait for completion
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    cout << "Final counter value: " << sharedCounter << endl;
    cout << "Expected: 1000" << endl;
    cout << "The actual value is often less due to race conditions!" << endl;
    
    return 0;
}
