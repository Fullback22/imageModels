#include "BlockMarkovModel.h"

void BlockMarkovModel::generateMap(int const transitionsStep)
{
	mapGenerator.initConditionalTransitions(transitionsStep);
	map = mapGenerator.generateStandartMainImage();
}

void BlockMarkovModel::generateMap(std::vector<std::vector<int>>* conditionalTransitions)
{
	mapGenerator.setConditionalTransitions(conditionalTransitions);
	map = mapGenerator.generateStandartMainImage();
}

BlockMarkovModel::BlockMarkovModel(cv::Size const* imageSize_, cv::Size const* blockSize_):
	blockSize{ *blockSize_ },
	imageSize{ *imageSize_ },
	mapGenerator{ imageSize_ }
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

cv::Mat BlockMarkovModel::generateStandartMainImage()
{
	generateMap(10);

	cv::Mat mainImage{ imageSize, CV_8UC1 };
	for (int y{ 0 }; y < map.size().height; ++y)
	{
		for (int x{ 0 }; x < map.size().width; ++x)
		{
			for (int i{ y * blockSize.height }; i < (y + 1) * blockSize.height && i < imageSize.height; ++i)
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

cv::Mat BlockMarkovModel::generateStandartMainImage(int const transitionsStep)
{
	generateMap(transitionsStep);

	cv::Mat mainImage{ imageSize, CV_8UC1 };
	for (int y{ 0 }; y < map.size().height; ++y)
	{
		for (int x{ 0 }; x < map.size().width; ++x)
		{
			for (int i{ y * blockSize.height }; i < (y + 1) * blockSize.height && i < imageSize.height; ++i)
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

cv::Mat BlockMarkovModel::generateStandartMainImage(std::vector<std::vector<int>>* conditionalTransitions)
{
	generateMap(conditionalTransitions);

	cv::Mat mainImage{ imageSize, CV_8UC1 };
	for (int y{ 0 }; y < map.size().height; ++y)
	{
		for (int x{ 0 }; x < map.size().width; ++x)
		{
			for (int i{ y * blockSize.height }; i < (y + 1) * blockSize.height && i < imageSize.height; ++i)
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
