#define _USE_MATH_DEFINES

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <vector>
#include <math.h>
#include <iostream>

double computePropability(float const x, float const mean, float const sko)
{
	double toSqr{ (x - mean) / sko };
	double toExp{ -0.5 * toSqr * toSqr };
	double numerator{ exp(toExp) };
	
	double toSqrt{ 2 * M_PI };
	double denumerator{ sqrt(toSqrt) * sko };

	return numerator / denumerator;
}

int main()
{
	cv::Size imageSize{ 600,400 };
	cv::Mat mainImage{ imageSize, CV_32FC1 };
	static std::random_device rd;
	static std::mt19937 gen(rd());
	float startSko{ 0.01 };
	float startMean{ 0.5 };
	cv::Mat mean{ imageSize, CV_32FC1 };
	std::normal_distribution<float> dist(startMean, startSko);
	for (int i{ 0 }; i < imageSize.height; ++i)
	{
		for (int j{ 0 }; j < imageSize.width; ++j)
		{
			mainImage.at<float>(i, j) = dist(gen);
			mean.at<float>(i, j) = startMean;
		}
	}

	for (int z{ 0 }; z < 1000; ++z)
	{
		for (int i{ 0 }; i < imageSize.height-1; ++i)
		{
			for (int j{ 0 }; j < imageSize.width-1; ++j)
			{
				float newMean{ (mainImage.at<float>(i,j) + mainImage.at<float>(i + 1,j) + mainImage.at<float>(i,j + 1)) / 3 };
				std::normal_distribution<float> newDist{ newMean, startSko };
				double newValue{ newDist(gen) };
				double propabilityNewValue{ computePropability(newValue, mainImage.at<float>(i,j), startSko) };
				double propabilityOldValue{ computePropability(mainImage.at<float>(i,j), mean.at<float>(i,j), startSko) };

				double a{ propabilityNewValue / propabilityOldValue };

				mean.at<float>(i, j) = mainImage.at<float>(i, j);
				if (a > 1.0)
				{
					mainImage.at<float>(i, j) = newValue;
				}
				else
				{
					std::uniform_real_distribution<> dis{ 0.0, 1.0 };
					double conversionPropability{ dis(gen) };
					if (conversionPropability < a)
						mainImage.at<float>(i, j) = newValue;
				}
				if (mainImage.at<float>(i, j) > 1.0)
					mainImage.at<float>(i, j) = 1.0;
				else if (mainImage.at<float>(i, j) < -1.0)
					mainImage.at<float>(i, j) = -1.0;
			}
		}
		cv::imshow("image", mainImage);
		cv::waitKey(20);
	}
	cv::normalize(mainImage, mainImage, 1.0, 0.0, cv::NORM_MINMAX);
	cv::imshow("image", mainImage);
	cv::waitKey();
	return 0;
}
