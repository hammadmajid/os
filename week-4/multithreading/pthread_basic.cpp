// g++ -std=c++17 -pthread pthread_basic.cpp -o pthread_basic

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void threadFunction(int threadId) {
    for (int i = 0; i < 3; i++) {
        cout << "Thread " << threadId << " executing iteration " << (i + 1) << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    cout << "=== BASIC MULTITHREADING ===" << endl;
    cout << "Creating 3 threads..." << endl;
    
    thread t1(threadFunction, 1);
    thread t2(threadFunction, 2);
    thread t3(threadFunction, 3);
    
    // Wait for all threads to complete
    t1.join();
    t2.join();
    t3.join();
    
    cout << "All threads completed!" << endl;
    
    return 0;
}
