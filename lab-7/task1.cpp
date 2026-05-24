#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

int shared_variable = 0;
mutex var_mutex;
condition_variable cv;

void producer() {
    for (int i = 1; i <= 5; i++) {
        {
            unique_lock<mutex> lock(var_mutex);
            shared_variable = i;
            cout << "Producer: Set shared_variable to " << shared_variable << endl;
        }
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer() {
    for (int i = 1; i <= 5; i++) {
        {
            unique_lock<mutex> lock(var_mutex);
            cv.wait(lock, [] { return shared_variable > 0; });
            cout << "Consumer: Read shared_variable = " << shared_variable << endl;
            shared_variable = 0;
        }
        cv.notify_one();
    }
}

int main() {
    cout << "Producer-Consumer: Shared Variable using Condition Variables" << endl;
    cout << "===========================================================" << endl;
    
    thread p(producer);
    thread c(consumer);
    
    p.join();
    c.join();
    
    cout << "Producer-Consumer completed" << endl;
    
    return 0;
}
