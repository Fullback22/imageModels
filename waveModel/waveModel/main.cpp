#include <random>
#include <iostream>
#include <numeric>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include"WaveModel.h"

int main()
{
	cv::Size imageSize{ 600,400 };

	WaveModel test{ &imageSize, 10 };

	cv::Mat mainImage{ test.generateStandartMainImage() };

	cv::imwrite("waveImage.png", mainImage);
	cv::imshow("image", mainImage);
	cv::waitKey();
}