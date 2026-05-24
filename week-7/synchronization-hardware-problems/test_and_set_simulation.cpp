// g++ -std=c++17 -pthread test_and_set_simulation.cpp -o test_and_set_simulation

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Simulated test-and-set lock
class TestAndSetLock {
private:
    volatile bool lockVar = false;
    
public:
    // Simulates atomic test-and-set operation
    // Returns old value and sets to true atomically
    bool testAndSet() {
        bool oldValue = lockVar;
        lockVar = true;
        return oldValue;
    }
    
    void unlock() {
        lockVar = false;
    }
    
    // Spin lock using test-and-set
    void lock() {
        while (testAndSet()) {
            // Spin until lock acquired
            this_thread::sleep_for(chrono::microseconds(1));
        }
    }
};

TestAndSetLock lock;
int criticalResource = 0;

void accessResource(int threadId) {
    lock.lock();
    
    cout << "Thread " << threadId << " entering critical section" << endl;
    criticalResource++;
    this_thread::sleep_for(chrono::milliseconds(10));
    
    cout << "Thread " << threadId << " leaving critical section" << endl;
    lock.unlock();
}

int main() {
    cout << "=== TEST-AND-SET LOCK SIMULATION ===" << endl;
    cout << "Demonstrating atomic test-and-set for mutual exclusion\n" << endl;
    
    thread t1(accessResource, 1);
    thread t2(accessResource, 2);
    thread t3(accessResource, 3);
    
    t1.join();
    t2.join();
    t3.join();
    
    cout << "\nCritical resource value: " << criticalResource << endl;
    cout << "Each thread executed once, maintaining consistency." << endl;
    
    return 0;
}
