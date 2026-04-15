#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1, m2;

void deadlock_t1() {
    m1.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m2.lock();
    std::cout << "deadlock t1\n";
    m2.unlock();
    m1.unlock();
}

void deadlock_t2() {
    m2.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m1.lock();
    std::cout << "deadlock t2\n";
    m1.unlock();
    m2.unlock();
}

void safe_t1() {
    std::lock(m1, m2);
    std::lock_guard<std::mutex> l1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> l2(m2, std::adopt_lock);
    std::cout << "safe t1\n";
}

void safe_t2() {
    std::lock(m1, m2);
    std::lock_guard<std::mutex> l1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> l2(m2, std::adopt_lock);
    std::cout << "safe t2\n";
}

int main() {
    {
        std::thread a(deadlock_t1), b(deadlock_t2);
        a.join();
        b.join();
    }
    {
        std::thread a(safe_t1), b(safe_t2);
        a.join();
        b.join();
    }
}
