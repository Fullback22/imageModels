#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <vector>

class SimpelTwiceRandomModel
{
	std::vector<float> correlationCoefficients{};
	cv::Size imageSize{};
	std::vector<cv::Mat> gausRandomFields{};
	std::vector<cv::Mat> randomCorrelationCoefficients{};
	cv::Mat randomMean{};
	cv::Mat randomStandatrDeviation{};
	int quantityCorrelationCoefficients{};

	float sigmaForGaus(float const sigmaForRandomCoeficients);
	cv::Mat generateSimpelRandomField(cv::Mat const gausRandomFields);
public:
	SimpelTwiceRandomModel(cv::Size* const imageSize, int quantityCorrelationCoefficients);
	void generateGausRandomFields(std::vector<float>* const sigmaForRandomCoeficients);
	void generateRandomCorrelationCoefficients();
	void generateRandomMean();
	void generateRandomStandatrDeviation();
};

