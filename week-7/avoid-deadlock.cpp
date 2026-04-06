#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mutex1, mutex2;

void thread1_func() {
    cout << "Thread 1: Locking mutex1..." << endl;
    mutex1.lock();
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Thread 1: Locking mutex2..." << endl;
    mutex2.lock();
    
    cout << "Thread 1: Got both mutexes!" << endl;
    
    mutex2.unlock();
    mutex1.unlock();
}

void thread2_func() {
    // SAME ORDER as thread1 - mutex1 FIRST, then mutex2
    cout << "Thread 2: Locking mutex1..." << endl;
    mutex1.lock();
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Thread 2: Locking mutex2..." << endl;
    mutex2.lock();
    
    cout << "Thread 2: Got both mutexes!" << endl;
    
    mutex2.unlock();
    mutex1.unlock();
}

int main() {
    cout << "=== DEADLOCK AVOIDANCE EXAMPLE ===" << endl;
    
    thread t1(thread1_func);
    thread t2(thread2_func);
    
    t1.join();
    t2.join();
    
    cout << "Both threads completed successfully!" << endl;
    
    return 0;
}
