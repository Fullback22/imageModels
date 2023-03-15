#include "BlockMarkovModel.h"

void BlockMarkovModel::generateMap(int const transitionsStep)
{
	mapGenerator_.initConditionalTransitions(transitionsStep);
	map_ = mapGenerator_.generateStandartMainImage();
}

void BlockMarkovModel::generateMap(const std::vector<std::vector<int>>& conditionalTransitions)
{
	mapGenerator_.setConditionalTransitions(conditionalTransitions);
	map_ = mapGenerator_.generateStandartMainImage();
}

BlockMarkovModel::BlockMarkovModel(const cv::Size& imageSize, const cv::Size& blockSize):
	blockSize_{ blockSize },
	imageSize_{ imageSize }
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
	mapGenerator_ = MarkovFields{ mapSize };
}

cv::Mat BlockMarkovModel::generateStandartMainImage(int const transitionsStep)
{
	generateMap(transitionsStep);
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

cv::Mat BlockMarkovModel::generateStandartMainImage(const std::vector<std::vector<int>>& conditionalTransitions)
{
	generateMap(conditionalTransitions);
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
