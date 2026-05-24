#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex resource1, resource2;
int lock_order = 0;  // Enforces global lock ordering: 1 before 2

void processAvoidance1() {
    cout << "Process 1: Attempting to lock Resource 1 (lower ID)..." << endl;
    resource1.lock();
    cout << "Process 1: Locked Resource 1" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Process 1: Attempting to lock Resource 2 (higher ID)..." << endl;
    resource2.lock();
    cout << "Process 1: Locked Resource 2" << endl;
    
    cout << "Process 1: Both resources acquired, doing work..." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    resource2.unlock();
    cout << "Process 1: Released Resource 2" << endl;
    resource1.unlock();
    cout << "Process 1: Released Resource 1" << endl;
}

void processAvoidance2() {
    cout << "Process 2: Attempting to lock Resource 1 (lower ID)..." << endl;
    resource1.lock();
    cout << "Process 2: Locked Resource 1" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Process 2: Attempting to lock Resource 2 (higher ID)..." << endl;
    resource2.lock();
    cout << "Process 2: Locked Resource 2" << endl;
    
    cout << "Process 2: Both resources acquired, doing work..." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    resource2.unlock();
    cout << "Process 2: Released Resource 2" << endl;
    resource1.unlock();
    cout << "Process 2: Released Resource 1" << endl;
}

int main() {
    cout << "Deadlock Avoidance: Resource Ordering Technique" << endl;
    cout << "================================================" << endl;
    cout << "\nDeadlock Prevention Strategy: Resource Ordering" << endl;
    cout << "- All processes must acquire resources in the SAME order" << endl;
    cout << "- This prevents circular wait condition" << endl;
    cout << "- Ordering Rule: Resource 1 BEFORE Resource 2\n" << endl;
    
    cout << "Process 1: Acquires Resource 1, then Resource 2" << endl;
    cout << "Process 2: Also acquires Resource 1, then Resource 2" << endl;
    cout << "          (Same order - avoids deadlock)\n" << endl;
    
    cout << string(60, '-') << endl;
    cout << "Execution Start:" << endl;
    cout << string(60, '-') << endl;
    
    thread t1(processAvoidance1);
    thread t2(processAvoidance2);
    
    t1.join();
    t2.join();
    
    cout << string(60, '-') << endl;
    cout << "\nResult: SUCCESS - No Deadlock Occurred!" << endl;
    cout << "All processes completed successfully\n" << endl;
    
    cout << "Comparison:" << endl;
    cout << "===========" << endl;
    cout << "WITHOUT Avoidance: Both processes get stuck waiting infinitely" << endl;
    cout << "WITH Avoidance: Processes acquire resources in order and proceed\n" << endl;
    
    cout << "Key Insight:" << endl;
    cout << "By enforcing a consistent resource acquisition order across" << endl;
    cout << "all processes, we break the circular wait condition that" << endl;
    cout << "causes deadlock." << endl;
    
    return 0;
}
