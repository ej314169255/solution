#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
using namespace std;
#define NUM_THREADS 2

void prodMatr(short pos, long** a, long** b, int oi, int oj, int first, int last, long *sumArray)
{
    int sum = 0;

    for (int k = first; k <= last; k++)
    {
        sum += a[oi][k] * b[k][oj];
    }
    sumArray[pos] = sum;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::thread threads[NUM_THREADS];
    long sumArray[NUM_THREADS] = {0};
    int n1, n2, m1, m2;
    long l = 0;
    long h = 255;
    srand(time(NULL));

    
    std::cin >> n1;
    std::cin >> m1;
    std::cin >> n2;
    std::cin >> m2;

    int step = n1 / NUM_THREADS;
    long** res = new long* [m1];
    long** a   = new long* [m1];
    long** b   = new long* [m1];
    
    for (int i = 0; i < m1; i++)
    {
        res[i] = new long[n1];
          a[i] = new long[n1];
          b[i] = new long[n1];
    }    

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            a[i][j] = l + rand() % ((h + 1) - l);
        }
    }

    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            b[i][j] = l + rand() % ((h + 1) - l);
        }
    }
   

    int cur_iteration = 0;
    int num_iteration = 9;
    int sum_time = 0;
    
    std::cout << "Start multithread thread calculation 10 counts" << std::endl;
    while (cur_iteration < num_iteration + 1)
    {
        cur_iteration++;
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                res[i][j] = 0;

               
                for (int y = 0; y < NUM_THREADS; y++) {

                    threads[y] = std::thread(prodMatr, y, a, b, i, j, y*step, (y+1) * step - 1, sumArray);                    
                }

                for (int y = 0; y < NUM_THREADS; y++) {
                    threads[y].join();
                }

                for (int y = 0; y < NUM_THREADS; y++) {
                    res[i][j] += sumArray[y];
                }
            }
        }
        auto end = std::chrono::system_clock::now();
        auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "number calculation is " << cur_iteration << "................ " << el_single << std::endl;
        sum_time += el_single;
        
    }
    std::cout << "End multithread calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;
    std::cout << "first element of matrix....." << res[0][0] << std::endl;
   cur_iteration = 0;
    num_iteration = 9;
    sum_time = 0;

    std::cout << "Start single calculation 10 counts" << std::endl;

    while (cur_iteration < num_iteration + 1)
    {
        cur_iteration++;
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                res[i][j] = 0;
                for (int k = 0; k < m1; k++)
                {
                    res[i][j] += a[i][k]*b[k][j];
                }
            }
        }
        auto end = std::chrono::system_clock::now();
        auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "number calculation is " << cur_iteration << "................ " << el_single << std::endl;
        sum_time += el_single;
        
    }
    std::cout << "End single calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;
    std::cout << "first element of matrix....." << res[0][0] << std::endl;
    return 0;
}
