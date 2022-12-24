#include<stdio.h>
#include "mpi.h"
#include <string>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <cstring>
#include <vector>
#include <iostream>

#define STR_LENGTH  5
using boost::uuids::detail::md5;
using namespace	std;
string found_string = "98EA8C591F4B843732CAE52D26AAC9F5";//0000j
string toString(const md5::digest_type& digest)
{
    const auto charDigest = reinterpret_cast<const char*>(&digest);
    string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    return result;
}

char alfphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int str_length = strlen(alfphabet);//62;
void strSearch(int first, int last)
{
    md5 hash;
    md5::digest_type digest;
    
    int stop = 0;

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
                        
                        std::string str(pass_serch);
                        hash.process_bytes(str.data(), str.size());
                        hash.get_digest(digest);
                        
                        
                        if (toString(digest) == found_string)
                        {
                                 
                            std::cout << "string found: " << pass_serch << "..... " << toString(digest) << std::endl;
                            stop = 1;                            
                            break;
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
    int a[] = { 0, 21 };//21
    int b[] = { 22, 42 };//42
    int c[] = { 43, 62 };//62
    int sym_index = 62;
    int stop = 0;
    MPI_Status status;
    MPI_Init(argc, &argv); // Инициализация MPI с аргументами из командной строки
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Определение процессом собственного номера
    MPI_Comm_size(MPI_COMM_WORLD, &numproc); // Определение числа процессов
    switch (rank) {
    case 0:
        MPI_Send(a, 2, MPI_INT, 1, TAG1, MPI_COMM_WORLD);
        MPI_Send(b, 2, MPI_INT, 2, TAG2, MPI_COMM_WORLD);
        MPI_Send(c, 2, MPI_INT, 3, TAG3, MPI_COMM_WORLD);
        
        break;
    case 1:
        MPI_Recv(a, 2, MPI_INT, 0, TAG1, MPI_COMM_WORLD, &status);
        strSearch(a[0], a[1]);
        
        break;
    case 2:
        MPI_Recv(b, 2, MPI_INT, 0, TAG2, MPI_COMM_WORLD, &status);
        strSearch(b[0], b[1]);
        
        break;
    case 3:
        MPI_Recv(c, 2, MPI_INT, 0, TAG3, MPI_COMM_WORLD, &status);
        strSearch(c[0], c[1]);
        
        break;
    default:
        printf("Process the message\n");
    }
   
    MPI_Finalize();
    return 0;
}