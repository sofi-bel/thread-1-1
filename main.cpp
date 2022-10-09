#include <iostream>
#include <thread>
#include <chrono>

#define NUM_THREADS 8

void sumFunction(unsigned int position, unsigned long long first, unsigned long long last, unsigned long long *sumArray) {
    unsigned long long sum = 0;
    for (unsigned long long i = first; i <= last; ++i) {
        sum += i;
    }
    sumArray[position] = sum;
}

int main() {
    std::thread threads[NUM_THREADS];
    unsigned long long sumArray[NUM_THREADS] = {0};
    unsigned long long sum1 = 0, sum2 = 0, N = 10000000000;
    unsigned long long step = N / NUM_THREADS;

    std::cout << "Start multithread calculation..." << std::endl;
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread(sumFunction, i, i * step + 1, (i + 1) * step, sumArray);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
        std::cout << "Thread " << i << " end calculation " << std::endl;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        sum1 += sumArray[i];
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "End multithread calculation... " << std::endl;
    std::cout << "Sum 1 = " << sum1 << " with time: " << elapsed1 << " msec" << std::endl;

    std::cout << "Start single thread calculation ..." << std::endl;
    start = std::chrono::system_clock::now();
    for (uint64_t i = 0; i < N; i++) {
        sum2 += i;
    }
    end = std::chrono::system_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "End single thread calculation... " << std::endl;
    std::cout << "Sum 2 = " << sum2 << " with time: " << elapsed2 << " msec" << std::endl;
}
