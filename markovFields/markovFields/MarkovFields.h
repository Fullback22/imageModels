#pragma once
#include <iostream>
#include <random>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

class MarkovFields
{
	cv::Size imageSize{};
	std::random_device rd;
	std::mt19937 gen{};
	std::vector<std::vector<int>> conditionalTransitions{};

	int getNewValue(std::vector<int>* frequncys);
public:
	MarkovFields(cv::Size const* imageSize);
	void initConditionalTransitions(int const transitionsStep);
	void setConditionalTransitions(std::vector<std::vector<int>> *conditionalTransitions);
	cv::Mat generateStandartMainImage();
};

