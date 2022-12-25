#include<stdio.h>
#include "mpi.h"
#include <chrono>
#include <time.h>
#include <iostream>
using namespace	std;

int n1 = 600;
int n2 = 600;
int m1 = 600;
int m2 = 600;

#define TAG1 200
#define TAG2 200
#define TAG3 200

void multy(long** a, long** b, int first, int last, unsigned long** res)
{
    for (int i = first; i < last; i++)
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
}

int main(int* argc, char** argv) {

    int i, rank, numproc;
    int low[] = { 0, 200 };
    int med[] = { 201, 400 };
    int hig[] = { 401, 600 };    

        char l(-128);
        char h(127);
        srand(time(NULL));
        unsigned long** res = new unsigned long* [m1];
        std::cout << "here going definess" << std::endl;
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

        MPI_Status status;
        MPI_Init(argc, &argv); // Инициализация MPI с аргументами из командной строки
        MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Определение процессом собственного номера
        MPI_Comm_size(MPI_COMM_WORLD, &numproc); // Определение числа процессов

        while (cur_iteration < num_iteration + 1)
        {
            cur_iteration++;
            auto start = std::chrono::system_clock::now();
           
            switch (rank) {
            case 0:
                //MPI_Send(array, 100, MPI_INT, 0, TAG1, MPI_COMM_WORLD);
                MPI_Send(low, 2, MPI_INT, 1, TAG1, MPI_COMM_WORLD);
                MPI_Send(med, 2, MPI_INT, 2, TAG2, MPI_COMM_WORLD);
                MPI_Send(hig, 2, MPI_INT, 3, TAG3, MPI_COMM_WORLD);
                break;
            case 1:
                MPI_Recv(low, 2, MPI_INT, 0, TAG1, MPI_COMM_WORLD, &status);
                
                multy(a, b, low[0], low[1], res);
                break;
            case 2:
                MPI_Recv(med, 2, MPI_INT, 0, TAG2, MPI_COMM_WORLD, &status);
                
                multy(a, b, med[0], med[1], res);
                break;
            case 3:
                MPI_Recv(hig, 2, MPI_INT, 0, TAG3, MPI_COMM_WORLD, &status);
                
                multy(a, b, hig[0], hig[1], res);
                break;
            default:
                printf("Process the message\n");
            }
            auto end = std::chrono::system_clock::now();
            auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "number calculation is " << cur_iteration << "................ " << el_single << std::endl;
            sum_time += el_single;
        }
        std::cout << "End multyplay calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;
        std::cout << "first element of matrix....." << res[0][0] << std::endl;
        MPI_Finalize();
        return 0;
    }
    


/*int main(int argc, char** argv)
{
    int numtasks, rank;
    printf("Before MPI_INIT\n");
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_rank(MPI_COMM_WORLD, &numtasks);
    printf("Parallel sect\n");
    printf("Hello MPI from process = %d, total number of processs: %d\n", rank, numtasks);

    MPI_Finalize();
    printf("After MPI_FINALIZE\n");
    return 0;
}*/


/*
int main()
{
    
    puts(md5.digestString("HELLO THERE I AM MD5!"));

    // print the digest for a binary file on disk.
    //puts(md5.digestFile("C:\\WINDOWS\\notepad.exe"));

    return 0;
}*/