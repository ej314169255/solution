#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
using namespace std;
#define NUM_THREADS 2

void sumFunction(unsigned int pos, unsigned long long first, unsigned long long last, unsigned long long *sumArray)
{
    unsigned long long sum = 0;
    for (unsigned long long i = first; i <= last; ++i)
    {
        sum += i;
    }
    sumArray[pos] = sum;
}

int main()
{
    std::thread threads[NUM_THREADS];
    unsigned long long sumArray[NUM_THREADS] = { 0 };
    unsigned long long N = 10000000000;
    unsigned long long step = N / NUM_THREADS;

    int cur_iteration = 0;
    int num_iteration = 9;
    int sum_time = 0;

    std::cout << "Start multithread thread calculation 10 counts" << std::endl;
    while (cur_iteration < num_iteration + 1)
    {
        cur_iteration++;
        unsigned long long sum1 = 0;
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < NUM_THREADS; i++) {
            threads[i] = std::thread(sumFunction, i, i * step + 1, (i + 1) * step, sumArray);
        }

        for (int i = 0; i < NUM_THREADS; i++) {
            threads[i].join();
            //std::cout << "Thread " << i << "end calculation " << std::endl;
        }
        for (int i = 0; i < NUM_THREADS; i++) {
            sum1 += sumArray[i];
        }
        auto end = std::chrono::system_clock::now();
        auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "number calculation is " << cur_iteration << "................ " << el_single << std::endl;
        sum_time += el_single;
    }
    std::cout << "End multithread calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;

    cur_iteration = 0;
    num_iteration = 9;
    sum_time = 0;

    std::cout << "Start single calculation 10 counts" << std::endl;
    while (cur_iteration < num_iteration + 1)
    {
        cur_iteration++;
        unsigned long long sum2 = 0;
        auto start = std::chrono::system_clock::now();
        for (uint64_t y = 1; y <= N; y++) {
            sum2 += y;
        }
        auto end = std::chrono::system_clock::now();
        auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "number calculation is " << cur_iteration << "................ " << el_single << std::endl;
        sum_time += el_single;
    }
    std::cout << "End single calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;

    auto start2 = std::chrono::system_clock::now();
    
    return 0;
}
