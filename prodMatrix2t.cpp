#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <ctime>
using namespace std;

#define NUM_THREADS 2

void prodMatr(unsigned int** a, unsigned int** b, unsigned int oi, unsigned int oj, unsigned int first, unsigned int last, unsigned long sum)
{
    unsigned long s = 0;
    //for (unsigned int j = oi; j < pos; j++)
    //{
        for (unsigned int k = first; k < last;)
        {
            s += a[oi][k] * b[k][oj];
            k++;
        }
        sum = s;
    //}
}
void threadFunction(unsigned int a)
{
    unsigned long sum = 0;
    for (unsigned int k = 0; k < 15;)
    {
         ++a;
        k++;
    }
    //SumArray[pos] = sum;

}

int main()
{
    //thread thr;
    setlocale(LC_ALL, "Russian");
    unsigned int n1, n2, m1, m2;
    unsigned int i, j;
    //unsigned int** a, ** b;
    unsigned long** c = nullptr;
    unsigned long sum = 0;
    unsigned long x;
    long int a[][2] = { {3,5}, {2,6} };
    long int b[][2] = { {1,8}, {2,7} };
    n1 = n2 = m1 = m2 = 2;
    /*std::cin >> n1;
    std::cin >> m1;
    std::cin >> n2;
    std::cin >> m2;*/

    unsigned int step = m1 / NUM_THREADS;

    /*a = new unsigned int* [n1];
    for (i = 0; i < n1; i++)
    {
        a[i] = new unsigned int[m1];
    }

    b = new unsigned int* [n2];
    for (i = 0; i < n2; i++)
    {
        b[i] = new unsigned int[m2];
    }

    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < m1; j++)
        {
            a[i][j] = rand();
        }
    }

    for (i = 0; i < n2; i++)
    {
        for (j = 0; j < m2; j++)
        {
            b[i][j] = rand();
        }
    }
    */
    unsigned long** res;
    res = new unsigned long* [n1];
    for (i = 0; i < m2; i++)
    {
        res[i] = new unsigned long[m2];
    }

    unsigned int cur_iteration = 0;
    unsigned int num_iteration = 9;
    unsigned long sum_time = 0;

    std::cout << "Start single thread calculation 10 counts" << std::endl;
    while (cur_iteration < num_iteration + 1)
    {
        cur_iteration++;

        auto start1 = std::chrono::system_clock::now();

        for (i = 0; i < n1; i++)
        {
            for (j = 0; j < m2; j++)
            {
                res[i][j] = 0;

                for (int k = 0; k < m1; k++)
                {
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        auto end1 = std::chrono::system_clock::now();
        auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
        std::cout << "Curent calculation with time: " << el_single << std::endl;
        sum_time += el_single;

    }
    cout << res[0][0] << endl;
    std::cout << "End single thread calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;

    std::cout << "Start multithread calculation 10 counts" << std::endl;
    cur_iteration = 0;
    num_iteration = 9;
    sum_time = 0;
    while (cur_iteration < num_iteration + 1)
    {
        cur_iteration++;

        auto start = std::chrono::system_clock::now();

        for (i = 0; i < n1; i++)
        {
            for (j = 0; j < m2; j++)
            {
                res[i][j] = 0;

                //for (unsigned int y = 0; y < NUM_THREADS; y++) {
                    std::thread thr(threadFunction, x);
                    //std::thread thr(prodMatr, a, b, i, j, (y-1)*step, y * step, sum);
                    std::cout <<x<< std::endl;
                    thr.join();
               // }
              //  for (unsigned int y = 0; y < NUM_THREADS; y++) {
                  //      thread thr.join();
                  //  }

                //for (unsigned int y = 0; y < NUM_THREADS; y++) {
                 //      res[i][j] += sumArray[y];
                 //   }
                 //  std::cout << res[i][j] << "\t";
            }
           // cout << endl;
        }
        //   cout << endl;

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        //std::cout << "Curent calculation with time: " << elapsed << std::endl;
        sum_time += elapsed;

    }
   // cout << res[0][0] << endl;
    //std::cout << "End multithread calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;
    return 0;
}
