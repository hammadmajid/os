#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex resource1, resource2;

void processDeadlock1() {
    cout << "Process 1: Attempting to lock Resource 1..." << endl;
    resource1.lock();
    cout << "Process 1: Locked Resource 1" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Process 1: Attempting to lock Resource 2..." << endl;
    resource2.lock();
    cout << "Process 1: Locked Resource 2" << endl;
    
    cout << "Process 1: Both resources acquired, doing work..." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    resource2.unlock();
    resource1.unlock();
    cout << "Process 1: Released both resources" << endl;
}

void processDeadlock2() {
    cout << "Process 2: Attempting to lock Resource 2..." << endl;
    resource2.lock();
    cout << "Process 2: Locked Resource 2" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Process 2: Attempting to lock Resource 1..." << endl;
    resource1.lock();
    cout << "Process 2: Locked Resource 1" << endl;
    
    cout << "Process 2: Both resources acquired, doing work..." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    resource1.unlock();
    resource2.unlock();
    cout << "Process 2: Released both resources" << endl;
}

int main() {
    cout << "Deadlock Demonstration: Circular Wait Condition" << endl;
    cout << "================================================" << endl;
    cout << "\nScenario:" << endl;
    cout << "- Process 1 locks Resource 1, then waits for Resource 2" << endl;
    cout << "- Process 2 locks Resource 2, then waits for Resource 1" << endl;
    cout << "\nResult: DEADLOCK (Circular wait condition)" << endl;
    cout << "Both processes will block indefinitely\n" << endl;
    
    cout << "Starting threads (this may hang)..." << endl;
    cout << string(50, '-') << endl;
    
    // Set a timeout for the entire program
    thread t1(processDeadlock1);
    thread t2(processDeadlock2);
    
    // Wait with timeout
    auto start = chrono::high_resolution_clock::now();
    auto timeout = chrono::seconds(3);
    
    t1.join();
    t2.join();
    
    cout << string(50, '-') << endl;
    cout << "Program completed" << endl;
    
    return 0;
}
