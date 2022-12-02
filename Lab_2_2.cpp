#include <iostream>
#include <omp.h>
#include <chrono>
#include <time.h>
using namespace std;
const int THREAD_NUM = 2;

int n1 = 600;
int n2 = 600;
int m1 = 600;
int m2 = 600;

int main()
{
    char l(-128);
    char h(127);
    srand(time(NULL));
    unsigned long** res = new unsigned long* [m1];
    long** a = new long* [m1];
    long** b = new long* [m1];

    for (int i = 0; i < m1; i++)
    {
        res[i] = new unsigned long[n1];
        a[i] = new long[n1];
        b[i] = new long[n1];
    }

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            a[i][j] = l + rand() % (255);
        }
    }

    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            b[i][j] = l + rand() % (255);
        }
    }

    int cur_iteration = 0;
    int num_iteration = 9;
    int sum_time = 0;

    std::cout << "Start multyplay calculation 10 counts" << std::endl;

    while (cur_iteration < num_iteration + 1)
    {
        cur_iteration++;
        auto start = std::chrono::system_clock::now();
#pragma omp parallel for num_threads(THREAD_NUM) // параллельная секция
        
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < m2; j++)
                {
                    res[i][j] = 0;
                    for (int k = 0; k < m1; k++)
                    {
                        res[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
            
        auto end = std::chrono::system_clock::now();
        auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "number calculation is " << cur_iteration << "................ " << el_single << std::endl;
        sum_time += el_single;

    }
    std::cout << "End multyplay calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;
    std::cout << "first element of matrix....." << res[0][0] << std::endl;
    return 0;
}