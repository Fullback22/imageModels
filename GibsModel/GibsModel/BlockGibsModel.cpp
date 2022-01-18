#include "BlockGibsModel.h"

void BlockGibsModel::generateMap(std::vector<int>* const startFrequency, std::vector<std::vector<int>>* const propabilityMap, int const maxIter)
{
	map = mapGenerator.generateStandartMainImage(startFrequency, propabilityMap, maxIter, false);
}

BlockGibsModel::BlockGibsModel(cv::Size const* imageSize_, cv::Size const* blockSize_):
	blockSize{*blockSize_},
	imageSize{*imageSize_},
	mapGenerator{ *imageSize_ }
{
	cv::Size mapSize{};
	if (imageSize_->width % blockSize.width == 0)
		mapSize.width = imageSize_->width / blockSize.width;
	else
		mapSize.width = imageSize_->width / blockSize.width + 1;
	if (imageSize_->height % blockSize.height == 0)
		mapSize.height = imageSize_->height / blockSize.height;
	else
		mapSize.height = imageSize_->height / blockSize.height + 1;
	map = cv::Mat{ mapSize,CV_8UC1 };
}

cv::Mat BlockGibsModel::generateStandartMainImage()
{
	int quantityClasses = 4;
	std::vector<int> startFrenqce{ 1,1,1,1 };
	std::vector<std::vector<int>> propabilityMap(quantityClasses);
	propabilityMap[0] = std::vector<int>{ 5,1,1,1 };
	propabilityMap[1] = std::vector<int>{ 1,5,1,1 };
	propabilityMap[2] = std::vector<int>{ 1,1,5,1 };
	propabilityMap[3] = std::vector<int>{ 1,1,1,5 };
	generateMap(&startFrenqce, &propabilityMap, 10);

	cv::Mat mainImage{ imageSize, CV_8UC1 };
	for (int y{ 0 }; y < map.size().height; ++y)
	{
		for (int x{ 0 }; x < map.size().width; ++x)
		{
			for (int i{ y * blockSize.height }; i < (y + 1) * blockSize.height && i< imageSize.height; ++i)
			{
				for (int j{ x * blockSize.width }; j < (x + 1) * blockSize.width && j < imageSize.width; ++j)
				{
					mainImage.at<uchar>(i, j) = map.at<uchar>(y, x);
				}
			}
		}
	}

	return mainImage;
}
