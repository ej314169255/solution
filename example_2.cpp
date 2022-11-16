#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <omp.h>
#include <conio.h>

using namespace cv;
using namespace std;

const int THREAD_NUM = 1;

int main()
{
	Mat img = imread("C:\\Users\\ej175\\source\\repos\\Project4\\Project4\\dog.jpg"); // Открытие файла

	int width = 1024, height = 768;
	// int width = 1280, height = 960;
	// int width = 2048, height = 1536;

	Mat1i Iimg(height, width);

	unsigned int start_time = clock(); // начальное время

#pragma omp parallel for num_threads(THREAD_NUM) // параллельная секция
	// Массив значений интенсивности исходного изображения
	for (int i = 0; i < Iimg.rows; i++) {
		for (int j = 0; j < Iimg.cols; j++)
		{
			Iimg[i][j] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
		}
	}

	// Ищем маскимальное значение интенсивности в массиве
	float Imax = 0.0;
	for (int i = 0; i < Iimg.rows; i++) {
		for (int j = 0; j < Iimg.cols; j++)
		{
			if (Iimg[i][j] > Imax)
				Imax = Iimg[i][j];
		}
	}

#pragma omp parallel for num_threads(THREAD_NUM)
	// Модифицируем исходный файл
	for (int i = 0; i < Iimg.rows; i++) {
		for (int j = 0; j < Iimg.cols; j++) {
			if (Iimg[i][j] < 0.2 * Imax) {
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 0;
				img.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time; // искомое время
	cout << "----- IMAGE SIZE " << width << " x " << height << " -----\n";
	cout << "----- THREAD NUMBER " << THREAD_NUM << " -----\n";
	cout << "----- RUNTIME " << search_time / 1000.0 << " -----\n";

	imwrite("D:\\Desktop\\tpu\\images\\dog_mono.jpg", Iimg);
	imwrite("D:\\Desktop\\tpu\\images\\dog_mod.jpg", img);
}