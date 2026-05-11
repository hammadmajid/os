#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

// Mutexes representing shared resources (mutex A and B)
mutex mutexA, mutexB;

/**
 * Thread 1 - Attempts to acquire mutexA then mutexB
 * This function locks resource A first, then tries to lock resource B.
 * If thread 2 has already locked B and is waiting for A, this creates a deadlock.
 */
void threadOneTask() {
    mutexA.lock();
    cout << "Thread 1 acquired Mutex A\n";

    mutexB.lock();
    cout << "Thread 1 acquired Mutex B\n";

    mutexB.unlock();
    mutexA.unlock();
}

/**
 * Thread 2 - Attempts to acquire mutexB then mutexA
 * This function locks resource B first, then tries to lock resource A.
 * If thread 1 has already locked A and is waiting for B, this creates a deadlock.
 * This is a classic example of circular wait - a necessary condition for deadlock.
 */
void threadTwoTask() {
    mutexB.lock();
    cout << "Thread 2 acquired Mutex B\n";

    mutexA.lock();
    cout << "Thread 2 acquired Mutex A\n";

    mutexA.unlock();
    mutexB.unlock();
}

int main() {
    // Create two threads that will likely cause a deadlock
    // Thread 1 locks A then waits for B, Thread 2 locks B then waits for A
    thread thread1(threadOneTask);
    thread thread2(threadTwoTask);

    // Wait for both threads to complete (they won't - deadlock!)
    thread1.join();
    thread2.join();

    return 0;
} 
