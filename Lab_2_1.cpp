#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <omp.h>
#include <conio.h>
#include <chrono>
#include <time.h>

using namespace cv;
using namespace std;

const int THREAD_NUM = 2;

int main()
{
	int width = 1024, height = 768;//1280 960 2048 1536
	//short v();
	Mat img_1 = imread("dog.jpg");
	Mat img_2 = imread("dog_mod.jpg");
	
	//Mat img_r(Size(height, width), CV_8UC3);
	Mat1i Iimg_1(height, width);
	Mat1i Iimg_2(height, width);
	Mat1i Iimg_v(height, width);

	int cur_iteration = 0;
	int num_iteration = 9;
	int sum_time = 0;

	std::cout << "Start multithread thread calculation 10 counts" << std::endl;
	while (cur_iteration < num_iteration + 1)
	{
		cur_iteration++;
		auto start = std::chrono::system_clock::now();
		#pragma omp parallel for num_threads(THREAD_NUM) // параллельная секция
		{

			for (int i = 0; i < Iimg_1.rows; i++) {
				for (int j = 0; j < Iimg_1.cols; j++)
				{
					Iimg_1[i][j] = (img_1.at<Vec3b>(i, j)[0] + img_1.at<Vec3b>(i, j)[1] + img_1.at<Vec3b>(i, j)[2]) / 3;
				}
			}

			for (int i = 0; i < Iimg_2.rows; i++) {
				for (int j = 0; j < Iimg_2.cols; j++)
				{
					Iimg_2[i][j] = (img_2.at<Vec3b>(i, j)[0] + img_2.at<Vec3b>(i, j)[1] + img_2.at<Vec3b>(i, j)[2]) / 3;
				}
			}
			for (int i = 0; i < Iimg_v.rows; i++) {
				for (int j = 0; j < Iimg_v.cols; j++)
				{
					Iimg_v[i][j] = ((Iimg_1[i][j] - Iimg_2[i][j]) + 255) / 2;
				}
			}
		}
		auto end = std::chrono::system_clock::now();
		auto el_single = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "number calculation is " << cur_iteration << "................ " << el_single << std::endl;
		sum_time += el_single;
		
	}
	std::cout << "End multithread calculation with avarege time: " << sum_time / (num_iteration + 1) << " milliseconds" << std::endl;
	cout << "----- IMAGE SIZE " << width << " x " << height << " -----\n";
	cout << "----- THREAD NUMBER " << THREAD_NUM << " -----\n";
	imwrite("bird_res.jpg", Iimg_v);
}