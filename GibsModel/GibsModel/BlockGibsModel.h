#pragma once
#include "GibsModel.h"
#include <iostream>

class BlockGibsModel
{
	cv::Mat map_{};
	cv::Size imageSize_{};
	cv::Size blockSize_{};
	GibsModel mapGenerator_{};
	void generateMap(const std::vector<int>& startFrequency, const std::vector<std::vector<int>>& propabilityMap, int const maxIter);
public:
	BlockGibsModel(const cv::Size& imageSize, const cv::Size& blockSize);
	cv::Mat generateStandartMainImage();
	cv::Mat generateStandartMainImage(const std::vector<int>& startFrequency,
									const std::vector<std::vector<int>>& propabilityMap,
									int const maxIter,
									bool showResult);
};

