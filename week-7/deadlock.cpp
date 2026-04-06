#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mutex1, mutex2;

void thread1_func() {
  cout << "Thread 1: Locking mutex1..." << endl;
  mutex1.lock(); // Thread 1 locks mutex1

  this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work

  cout << "Thread 1: Trying to lock mutex2..." << endl;
  mutex2.lock(); // Thread 1 waits for mutex2

  cout << "Thread 1: Got both mutexes!" << endl;

  mutex2.unlock();
  mutex1.unlock();
}

void thread2_func() {
  cout << "Thread 2: Locking mutex2..." << endl;
  mutex2.lock(); // Thread 2 locks mutex2

  this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work

  cout << "Thread 2: Trying to lock mutex1..." << endl;
  mutex1.lock(); // Thread 2 waits for mutex1

  cout << "Thread 2: Got both mutexes!" << endl;

  mutex1.unlock();
  mutex2.unlock();
}

int main() {
  cout << "=== DEADLOCK EXAMPLE ===" << endl;

  thread t1(thread1_func);
  thread t2(thread2_func);

  // Program will hang here - DEADLOCK!
  // Thread 1 has mutex1, wants mutex2
  // Thread 2 has mutex2, wants mutex1

  t1.join();
  t2.join();

  return 0;
}
