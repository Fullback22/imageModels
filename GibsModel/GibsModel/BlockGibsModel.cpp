#include "BlockGibsModel.h"

void BlockGibsModel::generateMap(const std::vector<int>& startFrequency, const std::vector<std::vector<int>>& propabilityMap, int const maxIter)
{
	map_ = mapGenerator_.generateStandartMainImage(startFrequency, propabilityMap, maxIter, false);
}

BlockGibsModel::BlockGibsModel(const cv::Size& imageSize, const cv::Size& blockSize) :
	blockSize_{ blockSize },
	imageSize_{ imageSize },
	mapGenerator_{ imageSize_ }
{
	cv::Size mapSize{};
	if (imageSize_.width % blockSize.width == 0)
		mapSize.width = imageSize_.width / blockSize.width;
	else
		mapSize.width = imageSize_.width / blockSize.width + 1;
	if (imageSize_.height % blockSize.height == 0)
		mapSize.height = imageSize_.height / blockSize.height;
	else
		mapSize.height = imageSize_.height / blockSize.height + 1;
	map_ = cv::Mat{ mapSize, CV_8UC1 };
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
	generateMap(startFrenqce, propabilityMap, 10);

	cv::Mat mainImage{ imageSize_, CV_8UC1 };
	for (int y{ 0 }; y < map_.size().height; ++y)
	{
		for (int x{ 0 }; x < map_.size().width; ++x)
		{
			for (int i{ y * blockSize_.height }; i < (y + 1) * blockSize_.height && i< imageSize_.height; ++i)
			{
				for (int j{ x * blockSize_.width }; j < (x + 1) * blockSize_.width && j < imageSize_.width; ++j)
				{
					mainImage.at<uchar>(i, j) = map_.at<uchar>(y, x);
				}
			}
		}
	}

	return mainImage;
}

cv::Mat BlockGibsModel::generateStandartMainImage(const std::vector<int>& startFrequency, const std::vector<std::vector<int>>& propabilityMap, int const maxIter, bool showResult)
{
	generateMap(startFrequency, propabilityMap, maxIter);

	cv::Mat mainImage{ imageSize_, CV_8UC1 };
	for (int y{ 0 }; y < map_.size().height; ++y)
	{
		for (int x{ 0 }; x < map_.size().width; ++x)
		{
			for (int i{ y * blockSize_.height }; i < (y + 1) * blockSize_.height && i < imageSize_.height; ++i)
			{
				for (int j{ x * blockSize_.width }; j < (x + 1) * blockSize_.width && j < imageSize_.width; ++j)
				{
					mainImage.at<uchar>(i, j) = map_.at<uchar>(y, x);
				}
			}
		}
	}

	return mainImage;
}
