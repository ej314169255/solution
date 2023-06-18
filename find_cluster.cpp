#include <iostream>
#include <sstream>
#include <fstream>
#include <mpi.h>
#include <algorithm>
#include <map>
#include <math.h>
#define filename "out_brook.csv"
#define TAG1 200
#define TAG2 200
#define TAG3 200
using namespace std;

int main(int *argc, char **argv)
{
    const unsigned int DIM1 = 2;
    const unsigned int DIM2 = 1000;
    const unsigned int NUM_CLUSTER = 7;

    int m, j, high_sale_price, low_sale_price, high_area, low_area;
    int brook_i[DIM1][DIM2];
    float brook[DIM1][DIM2];
    float index[NUM_CLUSTER][2];//number mean count
    float orderd_c[NUM_CLUSTER];
    int cluster_point[NUM_CLUSTER];//it is number couple point of brook_i
    unsigned int rand_value = DIM2;
    int l = 0;
    int h = 999;
    int cluster_own;
    float dist_c;
    srand(time(NULL));
    

        int rank, numproc;
        MPI_Status status;
        MPI_Init(argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &numproc);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
        if (rank == 0) 
        {           
            //read dataset
            ifstream work_file(filename);
            string line;
            char delimiter = ',';
            getline(work_file, line);

            j = 0; m = 0; high_sale_price = 0; low_sale_price = 90000000; high_area = 0; low_area = 5000;

            while (getline(work_file, line) && j < 1)
            {
                stringstream stream(line); // Преобразование строки в поток
                string id, tax_class, sale_price, healtharea;
                getline(stream, id, delimiter);
                getline(stream, tax_class, delimiter);
                getline(stream, sale_price, delimiter);
                getline(stream, healtharea, delimiter);
                int myint1 = stoi(sale_price);
                int myint2 = stoi(healtharea);
                brook_i[0][j] = stoi(sale_price);
                brook_i[1][j] = stoi(healtharea);
                /*cout << "==================" << endl;
                cout << "tax_class: " << tax_class << endl;
                cout << "sale_price: " << brook_i[0][j] << endl;
                cout << "healtharea: " << brook_i[1][j] << endl;*/
                high_sale_price = (brook_i[0][j] > high_sale_price) ? brook_i[0][j] : high_sale_price;
                low_sale_price = (brook_i[0][j] < low_sale_price) ? brook_i[0][j] : low_sale_price;
                high_area = (brook_i[1][j] > high_area) ? brook_i[1][j] : high_area;
                low_area = (brook_i[1][j] < low_area) ? brook_i[1][j] : low_area;
                j++;
            }
            work_file.close();

            for (int i = 0; i < DIM2; i++)
            {
                brook[0][i] = float(brook_i[0][i] - low_sale_price) / float(high_sale_price - low_sale_price);
                brook[1][i] = float(brook_i[1][i] - low_area) / float(high_area - low_area);
            }
            
            //mpisend to !=0
            for (int i = 1; i < numproc; i++)
            {
                MPI_Send(brook, 2 * 1000, MPI_FLOAT, i, TAG1, MPI_COMM_WORLD);
                
            }
        }
        else
        {
            if (rank != 0)
            {
                for (int u = 1; u < numproc; u++)
                {
                    MPI_Recv(brook, 2 * 1000, MPI_FLOAT, 0, TAG1, MPI_COMM_WORLD, &status);
                    
                    for (int i = 0; i < NUM_CLUSTER; i++)
                    {
                        cluster_point[i] = l + rand() % ((h + 1) - l);
                        index[i][0] = 0;
                        index[i][1] = 0;
                    }

                    for (int i = 0; i < DIM2; i++)
                    {
                        dist_c = 1;
                        for (int j = 0; j < NUM_CLUSTER; j++)
                        {
                            int cur_cluster_point = cluster_point[j];
                            orderd_c[j] = sqrt(pow((brook[1][i] - brook[1][cur_cluster_point]), 2) \
                                + pow((brook[0][i] - brook[0][cur_cluster_point]), 2));

                            if (orderd_c[j] < dist_c)
                            {
                                cluster_own = j;//number of cluster min distance
                                dist_c = orderd_c[j];
                            }
                        }
                        std::sort(orderd_c, orderd_c + NUM_CLUSTER);
                        if (orderd_c[1] > 0)
                        {
                            index[cluster_own][0] = index[cluster_own][0] + orderd_c[0] / orderd_c[1];
                            index[cluster_own][1]++;
                        }
                    }

                    float mean = 0;
                    for (int i = 0; i < NUM_CLUSTER; i++)
                    {
                        if (index[i][1] > 0)
                        {
                            float mean_cluster = 1 - index[i][0] / index[i][1];
                            mean = mean + mean_cluster;
                        }
                    }
                    cout << "The index of Wemmer-Gancarski is " << mean/NUM_CLUSTER << endl;
                }
            }
        }
       MPI_Finalize();
return 0;
}