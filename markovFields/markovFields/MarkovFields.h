#pragma once
#include <iostream>
#include <random>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

class MarkovFields
{
	cv::Size imageSize_{};
	std::random_device rd_{};
	std::mt19937 generator_{ rd_() };
	std::vector<std::vector<int>> conditionalTransitions_;

	int getNewValue(const std::vector<int>& frequncys);
public:
	MarkovFields();
	MarkovFields(const cv::Size& imageSize);
	MarkovFields& operator=(const MarkovFields& drop);
	void initConditionalTransitions(int const transitionsStep);
	void setConditionalTransitions(const std::vector<std::vector<int>> &conditionalTransitions);
	cv::Mat generateStandartMainImage();
};

