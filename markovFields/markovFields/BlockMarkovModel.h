#pragma once
#include "MarkovFields.h"

class BlockMarkovModel
{
	cv::Mat map{};
	cv::Size imageSize{};
	cv::Size blockSize{};
	MarkovFields mapGenerator;
	void generateMap(int const transitionsStep);
	void generateMap(std::vector<std::vector<int>>* conditionalTransitions);
public:
	BlockMarkovModel(cv::Size const* imageSize, cv::Size const* blockSize);
	cv::Mat generateStandartMainImage();
	cv::Mat generateStandartMainImage(int const transitionsStep);
	cv::Mat generateStandartMainImage(std::vector<std::vector<int>>* conditionalTransitions);
};

