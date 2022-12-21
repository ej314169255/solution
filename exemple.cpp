#include<stdio.h>
#include "mpi.h"
#include <windows.security.cryptography.h>
#include <string>
//#include <boost/uuid/detail/md5.hpp>
//#include <boost/md5.hpp>
#include <cstring>
#include <vector>
#include <iostream>
//#include <algorithm>
///#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
//#include <md5.h>
//#include <IdHashMessageDigest.hpp>
//#define NUM_THREADS 2
#define STR_LENGTH  5

using namespace	std;
//char str = "s";
char alfphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
void strSearch(int first, int last, int str_length)
{
    //char alfphabet[256];
    //int sym_index = 0;
   // for (int i = 0x20; i < 0x7F; i++) {
    //    alfphabet[sym_index] = i;
    //    sym_index++;
    //}

    //int str_length = sym_index;
    int stop = 0;
    //std::cout << "Alphabet (length = " << str_length << "):" << std::endl;
    //for (int i = 0; i < sym_index; i++) {
    //    std::cout << alfphabet[i];
    //}
    //std::cout << std::endl;

//#pragma omp parallel for
    for (int i = first; i < last; i++)
    {
        if (stop) break;
        for (int j = 0; j < str_length; j++)
        {
            if (stop) break;
            for (int k = 0; k < str_length; k++)
            {
                if (stop) break;
                for (int l = 0; l < str_length; l++)
                {
                    if (stop) break;
                    for (int m = 0; m < str_length; m++)
                    {
                        if (stop) break;
                        char pass_serch[6];
                        pass_serch[0] = alfphabet[i];
                        pass_serch[1] = alfphabet[j];
                        pass_serch[2] = alfphabet[k];
                        pass_serch[3] = alfphabet[l];
                        pass_serch[4] = alfphabet[m];
                        pass_serch[5] = '\0';
                        std::cout << "founding :)" << std::endl;
                        //if (strcmp(pass_serch, 'y') == 0)
                        {
                            {                                
                                //stop = 1;
                            }
                            //break;
                        }
                    }
                }

            }
        }
    }
    if (!stop)
        std::cout << "string not found :(" << std::endl;
}

#define TAG1 37
#define TAG2 38
#define TAG3 39
int main(int* argc, char** argv) {
    int i, rank, numproc;
    int a[] = { 1, 21 };
    int b[] = { 22, 42 };
    int c[] = { 43, 62 };
    int sym_index = 62;
    int str_length = sym_index;
    int stop = 0;
    MPI_Status status;
    MPI_Init(argc, &argv); // Инициализация MPI с аргументами из командной строки
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Определение процессом собственного номера
    MPI_Comm_size(MPI_COMM_WORLD, &numproc); // Определение числа процессов
    switch (rank) {
    case 0:
       
        //MPI_Send(array, 100, MPI_INT, 0, TAG1, MPI_COMM_WORLD);
        MPI_Send(a, 2, MPI_INT, 1, TAG1, MPI_COMM_WORLD);
        MPI_Send(b, 2, MPI_INT, 2, TAG1, MPI_COMM_WORLD);
        MPI_Send(c, 2, MPI_INT, 3, TAG1, MPI_COMM_WORLD);
        printf("The main process has sent the message...\n");
        break;
    case 1:
        MPI_Recv(a, 2, MPI_INT, 0, TAG1, MPI_COMM_WORLD, &status);
        for (i = 0; i < 2; i++)
        {
            std::cout << "Time: " << a[i] << std::endl;
        }
        strSearch(a[0], a[1], str_length);
        printf("Process 1 has recieved the message\n");
        break;
    case 2:
        MPI_Recv(b, 2, MPI_INT, 0, TAG1, MPI_COMM_WORLD, &status);
        for (i = 0; i < 2; i++)
        {
            std::cout << "Time: " << b[i] << std::endl;
        }
        strSearch(b[0], b[1], str_length);
        printf("Process 2 has recieved the message\n");
        break;
    case 3:
        MPI_Recv(c, 2, MPI_INT, 0, TAG1, MPI_COMM_WORLD, &status);
        for (i = 0; i < 2; i++)
        {
            std::cout << "Time: " << c[i] << std::endl;
        }
        strSearch(c[0], c[1], str_length);
        printf("Process 3 has recieved the message\n");
        break;
    default:
        printf("Process the message\n");
    }
   
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