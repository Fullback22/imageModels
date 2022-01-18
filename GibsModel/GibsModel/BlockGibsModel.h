#pragma once
#include "GibsModel.h"
#include <iostream>

class BlockGibsModel
{
	cv::Mat map{};
	cv::Size imageSize{};
	cv::Size blockSize{};
	GibsModel mapGenerator;
	void generateMap(std::vector<int>* const startFrequency, std::vector<std::vector<int>>* const propabilityMap, int const maxIter);
public:
	BlockGibsModel(cv::Size const* imageSize, cv::Size const * blockSize);
	cv::Mat generateStandartMainImage();
};

