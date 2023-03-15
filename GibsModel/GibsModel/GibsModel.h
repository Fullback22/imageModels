#pragma once
#include <random>
#include <iostream>
#include <numeric>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class GibsModel
{
	cv::Size imageSize_{};
	cv::Mat mainImage_{};
	std::random_device rd_;
	std::mt19937 gen_;
	int quantityClasses_{};
	std::vector<std::vector<int>> propabilityMap_{};
	
	int getValueFromPropabilityMap(int const firstClass, int const secondClass) const;
	int generateNewValue(std::vector<int>* const ProbabilityDensity);
	std::vector<int> computeProbabilityDensity1(int const x, int const y);
	std::vector<int> computeProbabilityDensity2(int const x, int const y);
	std::vector<int> computeProbabilityDensity3(int const x, int const y);
	std::vector<int> computeProbabilityDensity4(int const x, int const y);
	std::vector<int> computeProbabilityDensity5(int const x, int const y);
	std::vector<int> computeProbabilityDensity6(int const x, int const y);
	std::vector<int> computeProbabilityDensity7(int const x, int const y);
	std::vector<int> computeProbabilityDensity8(int const x, int const y);
	std::vector<int> computeProbabilityDensity9(int const x, int const y);
	void generatePart1();
	void generatePart2();
	void generatePart3();
	void generatePart4();
	void generatePart5();
	void generatePart6();
	void generatePart7();
	void generatePart8();
	void generatePart9();
public:
	GibsModel(const cv::Size &imageSize);
	void setPropabilityMap(std::vector<std::vector<int>>* const propabilityMap);
	void initMainImage(std::vector<int>* frequencyClasses);
	void generateMainImage(int const iteration=100, bool showresult = false);
	void showResult();
	cv::Mat generateStandartMainImage();
	cv::Mat generateStandartMainImage(std::vector<int>* const startFrequency,
									std::vector<std::vector<int>>* const propabilityMap,
									int const maxIter,
									bool showResult);
	cv::Mat getMainImage() const;
};

