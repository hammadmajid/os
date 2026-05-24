#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 3;
int shared_buffer[BUFFER_SIZE];
int buffer_count = 0;
mutex buffer_mutex;
condition_variable cv_producer, cv_consumer;

void producer(int producer_id) {
    for (int i = 1; i <= 5; i++) {
        {
            unique_lock<mutex> lock(buffer_mutex);
            // Wait if buffer is full
            cv_producer.wait(lock, [] { return buffer_count < BUFFER_SIZE; });
            
            shared_buffer[buffer_count] = (producer_id * 100) + i;
            cout << "Producer " << producer_id << " produced data: " << shared_buffer[buffer_count] 
                 << " (Buffer size: " << buffer_count + 1 << "/" << BUFFER_SIZE << ")" << endl;
            buffer_count++;
        }
        cv_consumer.notify_one();
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

void consumer(int consumer_id) {
    for (int i = 1; i <= 3; i++) {
        {
            unique_lock<mutex> lock(buffer_mutex);
            // Wait if buffer is empty
            cv_consumer.wait(lock, [] { return buffer_count > 0; });
            
            int data = shared_buffer[buffer_count - 1];
            cout << "Consumer " << consumer_id << " consumed data: " << data 
                 << " (Buffer size: " << buffer_count - 1 << "/" << BUFFER_SIZE << ")" << endl;
            buffer_count--;
        }
        cv_producer.notify_one();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    cout << "Multiple Threads with Shared Buffer using Mutex and Condition Variables" << endl;
    cout << "=========================================================================" << endl;
    cout << "\nWithout proper synchronization:" << endl;
    cout << "- Data inconsistency may occur" << endl;
    cout << "- Both threads may access buffer simultaneously" << endl;
    cout << "- Buffer overflow/underflow issues" << endl;
    cout << "- Race conditions lead to unpredictable results" << endl;
    
    cout << "\nWith mutex locks and condition variables:" << endl;
    cout << "- Only one thread accesses buffer at a time" << endl;
    cout << "- Producer waits if buffer is full" << endl;
    cout << "- Consumer waits if buffer is empty" << endl;
    cout << "- Data consistency and synchronization ensured\n" << endl;
    
    // Create producer and consumer threads
    thread prod1(producer, 1);
    thread prod2(producer, 2);
    thread cons1(consumer, 1);
    thread cons2(consumer, 2);
    
    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();
    
    cout << "\nProgram completed successfully" << endl;
    cout << "Final buffer count: " << buffer_count << endl;
    
    return 0;
}
