#include <iostream>
#include <thread>
#include <semaphore>

int shared_variable = 0;
std::binary_semaphore sem(1); // Initialized to 1 (unlocked)

void increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        sem.acquire(); // wait()
        shared_variable++;
        sem.release(); // signal()
    }
}

int main() {
    const int iterations = 100000;

    std::thread t1(increment, iterations);
    std::thread t2(increment, iterations);

    t1.join();
    t2.join();

    std::cout << "Final Value: " << shared_variable << std::endl;
    return 0;
}
