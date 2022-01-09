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

	float sigmaForGaus(float const sigmaForRandomCoeficients);
	cv::Mat generateSimpelRandomField(cv::Mat const gausRandomFields);
	void changeMeanInRandomFields(cv::Mat& inOutputImage, float const newMean);
public:
	SimpelTwiceRandomModel(cv::Size* const imageSize, std::vector<float>* correlationCoefficients);
	void generateGausRandomFields(std::vector<float>* const sigmaForRandomCoeficients);
	void generateRandomCorrelationCoefficients();
	void generateRandomMean();
	void generateRandomStandatrDeviation();
	void changeMeanInRandomMean(float const newMean);
	void changeMeanInStandatrDeviation(float const newMean);
	cv::Mat generateMainImage();
	cv::Mat generateStandartMainImage();
	cv::Mat generateStandartMainImage(std::vector<float>* const sigmaForRandomCorrelationCoeficients,
										float const sigmaForRandomMean, 
										float const sigmaForRandomStdDeviation, 
										float const meanForRandomMean,
										float const meanForRandomStdDeviation,
										float const sigmaForMainImage,
										bool const normolizeImage = true);
	cv::Mat normolizeImage(cv::Mat& inOutputImage);
	std::vector<cv::Mat> getRandomCorrelationCoefficients() const;
};

