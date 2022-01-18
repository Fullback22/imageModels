#pragma once
#include <random>
#include <iostream>
#include <numeric>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class WaveModel
{
	int const deltaT { 1 };
	cv::Mat mainImage{};
	int densityPuasonDist{};
	std::random_device rd{};
	std::mt19937 gen{};
	std::vector<cv::Point> waveCenter{};
	std::vector<double> R{};
	std::vector<double> ksi{};
	void generateWaveParams(float const propabilityThreshold, float const meanRadius, float const skoRadius, float const meanBrightness, float const skoBrightness);
public:
	WaveModel(cv::Size const* imageSize, int const densityPuasonDist);
	cv::Mat generateStandartMainImage();
	cv::Mat generateStandartMainImage(float const propabilityThreshold, 
									float const meanRadius,
									float const skoRadius,
									float const meanBrightness,
									float const skoBrightness,
									float const iteration,
									double const attenuation,
									double const waveAmplification);
};

