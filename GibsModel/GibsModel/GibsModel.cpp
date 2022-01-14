#include "GibsModel.h"

int GibsModel::getValueFromPropabilityMap(int const firstClass, int const secondClass) const
{
	return propabilityMap[firstClass][secondClass];
}

int GibsModel::generateNewValue(std::vector<int>* const ProbabilityDensity)
{
	int allValue{ std::accumulate(ProbabilityDensity->begin(),ProbabilityDensity->end(),0) };
	std::uniform_int_distribution<> initDist{ 0, quantityClasses - 1 };
	std::uniform_real_distribution<> dis{ 0.0, 1.0 };
	for (; ;)
	{
		int newValue{ initDist(gen) };
		double propabilityNewValue{ static_cast<double>((*ProbabilityDensity)[newValue]) / allValue };
		double conversionPropability{ dis(gen) };
		if (conversionPropability < propabilityNewValue)
		{
			return newValue;
		}
	}
}

std::vector<int> GibsModel::computeProbabilityDensity1(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y + 1, x));
	startFrequency[mainImage.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity2(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y + 1, x));
	startFrequency[mainImage.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x + 1));
	startFrequency[mainImage.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity3(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y + 1, x));
	startFrequency[mainImage.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity4(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y + 1, x));
	startFrequency[mainImage.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y - 1, x));
	startFrequency[mainImage.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity5(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y - 1, x));
	startFrequency[mainImage.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity6(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y - 1, x));
	startFrequency[mainImage.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x + 1));
	startFrequency[mainImage.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity7(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y - 1, x));
	startFrequency[mainImage.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity8(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y + 1, x));
	startFrequency[mainImage.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y - 1, x));
	startFrequency[mainImage.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity9(int const x, int const y)
{
	std::vector<int> startFrequency(quantityClasses, 0);
	startFrequency[mainImage.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y + 1, x));
	startFrequency[mainImage.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y - 1, x));
	startFrequency[mainImage.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x + 1));
	startFrequency[mainImage.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage.at<uchar>(y, x), mainImage.at<uchar>(y, x - 1));
	return startFrequency;
}

void GibsModel::initMainImage(std::vector<int>* frequencyClasses)
{
	std::discrete_distribution<int> initImageDist{ frequencyClasses->begin(), frequencyClasses->end() };
	for (int i{ 0 }; i < imageSize.height; ++i)
	{
		for (int j{ 0 }; j < imageSize.width; ++j)
		{
			mainImage.at<uchar>(i, j) = initImageDist(gen);
		}
	}
}



void GibsModel::generatePart1()
{
	std::vector<int> startFrenqce(computeProbabilityDensity1(0, 0));
	mainImage.at<uchar>(0, 0) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart2()
{
	for (int i{ 1 }; i < imageSize.width - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity2(i, 0));
		mainImage.at<uchar>(0, i) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart3()
{
	std::vector<int> startFrenqce(computeProbabilityDensity3(imageSize.width - 1, 0));
	mainImage.at<uchar>(0, imageSize.width - 1) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart4()
{
	for (int i{ 1 }; i < imageSize.height - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity4(imageSize.width - 1, i));
		mainImage.at<uchar>(i, imageSize.width - 1) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart5()
{
	std::vector<int> startFrenqce(computeProbabilityDensity5(imageSize.width - 1, imageSize.height - 1));
	mainImage.at<uchar>(imageSize.height - 1, imageSize.width - 1) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart6()
{
	for (int i{ 1 }; i < imageSize.width - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity6(i, imageSize.height - 1));
		mainImage.at<uchar>(imageSize.height - 1, i) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart7()
{
	std::vector<int> startFrenqce(computeProbabilityDensity7(0, imageSize.height - 1));
	mainImage.at<uchar>(imageSize.height - 1, 0) = generateNewValue(&startFrenqce);
}

void GibsModel::generatePart8()
{
	for (int i{ 1 }; i < imageSize.height - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity8(0, i));
		mainImage.at<uchar>(i, 0) = generateNewValue(&startFrenqce);
	}
}

void GibsModel::generatePart9()
{
	for (int j{ 1 }; j < imageSize.width - 1; ++j)
	{
		for (int i{ 1 }; i < imageSize.height - 1; ++i)
		{
			std::vector<int> startFrenqce(computeProbabilityDensity9(j, i));
			mainImage.at<uchar>(i, j) = generateNewValue(&startFrenqce);
		}
	}
}

GibsModel::GibsModel(cv::Size const imageSize_):
	imageSize{imageSize_},
	mainImage{imageSize_, CV_8UC1},
	gen{rd()}
{
}

void GibsModel::setPropabilityMap(std::vector<std::vector<int>>* const propabilityMap_)
{
	propabilityMap.assign(propabilityMap_->begin(), propabilityMap_->end());
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
	int step{ 255 / quantityClasses };
	cv::Mat showImage{ imageSize, CV_8UC1 };
	for (int i{ 0 }; i < imageSize.height; ++i)
	{
		for (int j{ 0 }; j < imageSize.width; ++j)
		{
			showImage.at<uchar>(i, j) = mainImage.at<uchar>(i, j) * step;
		}
	}
	cv::imshow("image", showImage);
	cv::waitKey(1);
}

cv::Mat GibsModel::generateStandartMainImage()
{
	quantityClasses = 4;
	std::vector<int> startFrenqce{ 1,1,1,1 };
	std::vector<std::vector<int>> propabilityMap(quantityClasses);
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
	quantityClasses = startFrequency->size();
	initMainImage(startFrequency);
	setPropabilityMap(propabilityMap);
	generateMainImage(maxIter, showResult);
	return getMainImage();
}

cv::Mat GibsModel::getMainImage() const
{
	return mainImage;
}
