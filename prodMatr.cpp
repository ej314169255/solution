#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <ctime>
using namespace std;

#define NUM_THREADS 2

void prodMatr(unsigned int pos, unsigned int** a, unsigned int** b, unsigned int oi, unsigned int oj, unsigned int first, unsigned int last, unsigned long* SumArray)
{
    unsigned long sum = 0;
    for (unsigned int k = first; k < last; k++)
    {
        sum += a[oi][k] * b[k][oj];
    }
    SumArray[pos] = sum;
}

int main()
{
    thread threads[NUM_THREADS-1];
    unsigned long sumArray[NUM_THREADS] = { 0 };
    setlocale(LC_ALL, "Russian");
    unsigned int n1, n2, m1, m2;
    unsigned int i, j;
    unsigned int** a, ** b;
    unsigned long** c = nullptr;
    
    std::cout << "Введите количество строк матрицы 1: ";
    cin >> n1;
    std::cout << "Введите количество столбцов матрицы 1: ";
    cin >> m1;
    std::cout << "Введите количество строк матрицы 2: ";
    cin >> n2;
    std::cout << "Введите количество столбцов матрицы 2: ";
    cin >> m2;
    unsigned int step = m1 / NUM_THREADS;

    a = new unsigned int* [n1];
    for (i = 0; i < n1; i++)
    {
        a[i] = new unsigned int[m1];
    }

    b = new unsigned int* [n2];
    for (i = 0; i < n2; i++)
    {
        b[i] = new unsigned int[m2];
    }

    cout << "Построение матрицы 1: \t" << endl;
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < m1; j++)
        {
//            a[i][j] = rand();
//            ++a[i][j];
            cin >> a[i][j];
//          cout <<a[i][j] << "\t";
        }
    }
    cout << endl;

    cout << "Построение матрицы 2: \t" << endl;
    for (i = 0; i < n2; i++)
    {
        for (j = 0; j < m2; j++)
        {
//            b[i][j] = rand();
//            ++b[i][j];
            cin >> b[i][j];
//          cout << b[i][j] << "\t";
        }
    }
    cout << endl;

    cout << "Результат : \t" << endl;
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
//                cout << res[i][j] << "\t";
            }
         }//cout << endl;
 
        auto end1 = std::chrono::system_clock::now();
        auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
        std::cout << "Curent calculation with time: " << el_single << std::endl;
        sum_time += el_single;

    }
    cout<<res[0][0]<< endl;
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
           
 /*              for (unsigned int y = 0; y < NUM_THREADS; y++) {
                    threads[y] = std::thread(prodMatr, y, a, b, i, j, (y-1)*step, y * step, sumArray);                  
                }*/ 
 //               threads[1] = std::thread(prodMatr, 0, a, b, i, j, 0, 1, sumArray);
                threads[2] = std::thread(prodMatr, 1, a, b, i, j, 1, 2, sumArray);
            //    threads[0].join();
             //   threads[1].join();
               // res[i][j] = sumArray[0] + sumArray[1];
                
  /*              for (unsigned int y = 0; y < NUM_THREADS; y++) {
                    threads[y].join();
                }
              
               for (unsigned int y = 0; y < NUM_THREADS; y++) {
                   res[i][j] += sumArray[y];
                }
               std::cout << res[i][j] << "\t";*/
            }
            cout << endl;
        }
     //   cout << endl;

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Curent calculation with time: " << elapsed << std::endl;
        sum_time += elapsed;
        
    }
    cout << res[0][0] << endl;
    std::cout << "End multithread calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;
            
    return 0;
}