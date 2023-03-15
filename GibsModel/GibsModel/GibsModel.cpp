#include "GibsModel.h"

int GibsModel::getValueFromPropabilityMap(int const firstClass, int const secondClass) const
{
	return propabilityMap_[firstClass][secondClass];
}

int GibsModel::generateNewValue(std::vector<int>* const ProbabilityDensity)
{
	int allValue{ std::accumulate(ProbabilityDensity->begin(),ProbabilityDensity->end(),0) };
	std::uniform_int_distribution<> initDist{ 0, quantityClasses_ - 1 };
	std::uniform_real_distribution<> dis{ 0.0, 1.0 };
	for (; ;)
	{
		int newValue{ initDist(gen_) };
		double propabilityNewValue{ static_cast<double>((*ProbabilityDensity)[newValue]) / allValue };
		double conversionPropability{ dis(gen_) };
		if (conversionPropability < propabilityNewValue)
		{
			return newValue;
		}
	}
}

std::vector<int> GibsModel::computeProbabilityDensity1(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity2(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity3(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity4(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity5(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity6(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity7(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity8(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity9(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses_, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

void GibsModel::initMainImage(std::vector<int>* frequencyClasses)
{
	std::discrete_distribution<int> initImageDist{ frequencyClasses->begin(), frequencyClasses->end() };
	for (int i{ 0 }; i < imageSize_.height; ++i)
	{
		for (int j{ 0 }; j < imageSize_.width; ++j)
		{
			mainImage_.at<uchar>(i, j) = initImageDist(gen_);
		}
	}
}



void GibsModel::generatePart1()
{
	std::vector<int> startFrenqce(computeProbabilityDensity1(0, 0));
	mainImage_.at<uchar>(0, 0) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart2()
{
	for (int i{ 1 }; i < imageSize_.width - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity2(i, 0));
		mainImage_.at<uchar>(0, i) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart3()
{
	std::vector<int> startFrenqce(computeProbabilityDensity3(imageSize_.width - 1, 0));
	mainImage_.at<uchar>(0, imageSize_.width - 1) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart4()
{
	for (int i{ 1 }; i < imageSize_.height - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity4(imageSize_.width - 1, i));
		mainImage_.at<uchar>(i, imageSize_.width - 1) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart5()
{
	std::vector<int> startFrenqce(computeProbabilityDensity5(imageSize_.width - 1, imageSize_.height - 1));
	mainImage_.at<uchar>(imageSize_.height - 1, imageSize_.width - 1) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart6()
{
	for (int i{ 1 }; i < imageSize_.width - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity6(i, imageSize_.height - 1));
		mainImage_.at<uchar>(imageSize_.height - 1, i) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart7()
{
	std::vector<int> startFrenqce(computeProbabilityDensity7(0, imageSize_.height - 1));
	mainImage_.at<uchar>(imageSize_.height - 1, 0) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart8()
{
	for (int i{ 1 }; i < imageSize_.height - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity8(0, i));
		mainImage_.at<uchar>(i, 0) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart9()
{
	for (int j{ 1 }; j < imageSize_.width - 1; ++j)
	{
		for (int i{ 1 }; i < imageSize_.height - 1; ++i)
		{
			std::vector<int> startFrenqce(computeProbabilityDensity9(j, i));
			mainImage_.at<uchar>(i, j) = generateNewValue(&startFrenqce);
		}
	}
}

GibsModel::GibsModel(const cv::Size& imageSize):
	imageSize_{imageSize},
	mainImage_{imageSize, CV_8UC1},
	gen_{rd_()}
{
}

void GibsModel::setPropabilityMap(std::vector<std::vector<int>>* const propabilityMap)
{
	propabilityMap_.assign(propabilityMap->begin(), propabilityMap->end());
}

void GibsModel::generateMainImage(int const iteration, bool showResult_)
{
	for (int z{ 0 }; z < iteration; ++z)
	{
		generatePart1();
		generatePart2();
		generatePart3();
		generatePart4();
		generatePart5();
		generatePart6();
		generatePart7();
		generatePart8();
		generatePart9();
		if (showResult_)
			showResult();
	}
}

void GibsModel::showResult()
{
	int step{ 255 / quantityClasses_ };
	cv::Mat showImage{ imageSize_, CV_8UC1 };
	for (int i{ 0 }; i < imageSize_.height; ++i)
	{
		for (int j{ 0 }; j < imageSize_.width; ++j)
		{
			showImage.at<uchar>(i, j) = mainImage_.at<uchar>(i, j) * step;
		}
	}
	cv::imshow("image", showImage);
	cv::waitKey(1);
}

cv::Mat GibsModel::generateStandartMainImage()
{
	quantityClasses_ = 4;
	std::vector<int> startFrenqce{ 1,1,1,1 };
	std::vector<std::vector<int>> propabilityMap(quantityClasses_);
	propabilityMap[0] = std::vector<int>{ 5,1,1,1 };
	propabilityMap[1] = std::vector<int>{ 1,5,1,1 };
	propabilityMap[2] = std::vector<int>{ 1,1,5,1 };
	propabilityMap[3] = std::vector<int>{ 1,1,1,5 };

	initMainImage(&startFrenqce);
	setPropabilityMap(&propabilityMap);
	generateMainImage(1000, true);

	return getMainImage();
}

cv::Mat GibsModel::generateStandartMainImage(std::vector<int>* const startFrequency, 
											std::vector<std::vector<int>>* const propabilityMap, 
											int const maxIter, 
											bool showResult)
{
	quantityClasses_ = startFrequency->size();
	initMainImage(startFrequency);
	setPropabilityMap(propabilityMap);
	generateMainImage(maxIter, showResult);
	return getMainImage();
}

cv::Mat GibsModel::getMainImage() const
{
	return mainImage_;
}
