#include <random>
#include <iostream>
#include <numeric>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "GibsModel.h"
#include "BlockGibsModel.h"

int main()
{
	cv::Size imageSize{ 600,400 };

	int quantityClasses{ 4 };
	std::vector<int> startFrenqce{ 1,1,1,1 };
	std::vector<std::vector<int>> propabilityMap(quantityClasses);

	/*propabilityMap[0] = std::vector<int>{ 5,1 };
	propabilityMap[1] = std::vector<int>{ 0,5 };*/

	propabilityMap[0] = std::vector<int>{ 5,1,1,1 };
	propabilityMap[1] = std::vector<int>{ 1,5,1,1 };
	propabilityMap[2] = std::vector<int>{ 1,1,5,1 };
	propabilityMap[3] = std::vector<int>{ 1,1,1,5 };



	GibsModel test{ imageSize };
	cv::Size blockSize{ 10,10 };
	BlockGibsModel test1{&imageSize, &blockSize};
	cv::Mat showImage{ test1.generateStandartMainImage() };
	//cv::Mat showImage{ test.generateStandartMainImage(&startFrenqce, &propabilityMap, 500, true) };
	
	int step{ 255 / quantityClasses };
	for (int i{ 0 }; i < imageSize.height; ++i)
	{
		for (int j{ 0 }; j < imageSize.width; ++j)
		{
			showImage.at<uchar>(i, j) = showImage.at<uchar>(i, j) * step;
		}
	}
	cv::imwrite("gibsModel.png", showImage);
	cv::imshow("image", showImage);
	cv::waitKey();
}