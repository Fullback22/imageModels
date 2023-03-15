#pragma once
#include "MarkovFields.h"

class BlockMarkovModel
{
	cv::Mat map_{};
	cv::Size imageSize_{};
	cv::Size blockSize_{};
	MarkovFields mapGenerator_{};
	void generateMap(int const transitionsStep);
	void generateMap(const std::vector<std::vector<int>>& conditionalTransitions);
public:
	BlockMarkovModel(const cv::Size& imageSize, const cv::Size& blockSize);
	cv::Mat generateStandartMainImage(int const transitionsStep = 10);
	cv::Mat generateStandartMainImage(const std::vector<std::vector<int>>& conditionalTransitions);
};

