#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5;
int buffer[BUFFER_SIZE];
int buffer_count = 0;
mutex buffer_mutex;
condition_variable cv_full, cv_empty;

void supplier(int supplier_id) {
    for (int i = 1; i <= 8; i++) {
        {
            unique_lock<mutex> lock(buffer_mutex);
            // Wait if buffer is full
            cv_full.wait(lock, [] { return buffer_count < BUFFER_SIZE; });
            
            buffer[buffer_count] = (supplier_id * 100) + i;
            cout << "Supplier " << supplier_id << " added product " << buffer[buffer_count] 
                 << " to warehouse (Buffer: " << buffer_count + 1 << "/" << BUFFER_SIZE << ")" << endl;
            buffer_count++;
        }
        cv_empty.notify_one();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void customer(int customer_id) {
    for (int i = 1; i <= 4; i++) {
        {
            unique_lock<mutex> lock(buffer_mutex);
            // Wait if buffer is empty
            cv_empty.wait(lock, [] { return buffer_count > 0; });
            
            int product = buffer[buffer_count - 1];
            cout << "Customer " << customer_id << " removed product " << product 
                 << " from warehouse (Buffer: " << buffer_count - 1 << "/" << BUFFER_SIZE << ")" << endl;
            buffer_count--;
        }
        cv_full.notify_one();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    cout << "Warehouse Management System - Producer-Consumer Problem" << endl;
    cout << "==========================================================" << endl;
    cout << "Buffer capacity: " << BUFFER_SIZE << endl << endl;
    
    // Create supplier and customer threads
    thread sup1(supplier, 1);
    thread sup2(supplier, 2);
    thread cust1(customer, 1);
    thread cust2(customer, 2);
    
    sup1.join();
    sup2.join();
    cust1.join();
    cust2.join();
    
    cout << "\nWarehouse Management System completed" << endl;
    cout << "Final buffer count: " << buffer_count << endl;
    
    return 0;
}
