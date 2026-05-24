#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// Mutexes representing two rooms (shared resources)
mutex roomAMutex, roomBMutex;

/**
 * Ali's thread - Process 1
 * Ali attempts to lock Room A first, then Room B.
 * With a delay to allow Ahmed to run, this often causes a deadlock scenario.
 * Ali locks A, Ahmed locks B, then Ali waits for B and Ahmed waits for A -> DEADLOCK
 */
void aliThread() {
    roomAMutex.lock();  // Ali acquires Room A (roomAMutex)
    cout << "Ali acquired Room A (roomAMutex)" << endl;

    // Delay to allow Ahmed's thread to execute and lock Room B
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Ali is waiting for Room B (roomBMutex)..." << endl;
    roomBMutex.lock();  // Ali tries to acquire Room B (may cause deadlock)

    cout << "Ali acquired Room B (roomBMutex)" << endl;

    roomBMutex.unlock();
    roomAMutex.unlock();
}

/**
 * Ahmed's thread - Process 2
 * Ahmed attempts to lock Room B first, then Room A.
 * This is the opposite order from Ali, which creates the perfect condition for deadlock.
 * Ahmed locks B, Ali locks A, then Ahmed waits for A and Ali waits for B -> DEADLOCK
 */
void ahmedThread() {
    roomBMutex.lock();  // Ahmed acquires Room B (roomBMutex)
    cout << "Ahmed acquired Room B (roomBMutex)" << endl;

    // Delay to allow Ali's thread to execute and lock Room A
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Ahmed is waiting for Room A (roomAMutex)..." << endl;
    roomAMutex.lock();  // Ahmed tries to acquire Room A (may cause deadlock)

    cout << "Ahmed acquired Room A (roomAMutex)" << endl;

    roomAMutex.unlock();
    roomBMutex.unlock();
}

int main() {
    // Create two threads: Ali and Ahmed
    // They will attempt to lock resources in opposite orders, likely causing a deadlock
    thread aliThreadHandle(aliThread);
    thread ahmedThreadHandle(ahmedThread);

    // Wait for both threads to complete (they won't - circular wait deadlock!)
    aliThreadHandle.join();
    ahmedThreadHandle.join();

    return 0;
}
