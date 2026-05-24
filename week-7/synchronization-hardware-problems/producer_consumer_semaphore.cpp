// g++ -std=c++17 -pthread producer_consumer_semaphore.cpp -o producer_consumer_semaphore

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

// Simple semaphore implementation
class Semaphore {
private:
    int count;
    mutex mtx;
    
public:
    Semaphore(int initialCount = 0) : count(initialCount) {}
    
    // Wait (P operation) - decrement count
    void wait() {
        mtx.lock();
        while (count == 0) {
            mtx.unlock();
            this_thread::sleep_for(chrono::microseconds(10));
            mtx.lock();
        }
        count--;
        mtx.unlock();
    }
    
    // Signal (V operation) - increment count
    void signal() {
        mtx.lock();
        count++;
        mtx.unlock();
    }
};

int buffer[5];
int bufferIndex = 0;
Semaphore emptySem(5);   // 5 empty slots initially
Semaphore fullSem(0);    // 0 full slots initially
mutex bufferMutex;

void producer(int itemId) {
    cout << "Producer: producing item " << itemId << endl;
    
    emptySem.wait();  // Wait for empty slot
    
    bufferMutex.lock();
    buffer[bufferIndex] = itemId;
    cout << "Producer: placed item " << itemId << " in buffer[" << bufferIndex << "]" << endl;
    bufferIndex++;
    bufferMutex.unlock();
    
    fullSem.signal();  // Signal that buffer has item
}

void consumer(int consumerId) {
    fullSem.wait();  // Wait for full slot
    
    bufferMutex.lock();
    bufferIndex--;
    int item = buffer[bufferIndex];
    cout << "Consumer " << consumerId << ": consumed item " << item << endl;
    bufferMutex.unlock();
    
    emptySem.signal();  // Signal that slot is now empty
}

int main() {
    cout << "=== PRODUCER-CONSUMER WITH SEMAPHORES ===" << endl;
    cout << "Buffer size: 5 items\n" << endl;
    
    thread prod1(producer, 1);
    thread prod2(producer, 2);
    thread prod3(producer, 3);
    thread cons1(consumer, 1);
    thread cons2(consumer, 2);
    
    prod1.join();
    prod2.join();
    prod3.join();
    cons1.join();
    cons2.join();
    
    cout << "\nProducer-consumer completed successfully!" << endl;
    
    return 0;
}
