#include "GibsModel.h"

void GibsModel::generateImage(cv::Mat& inOutImage)
{
	initMainImage();
	for (size_t z{ 0 }; z < 100; ++z)
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
	}
	mainImage_.copyTo(inOutImage);
	unsigned int stepCoefficient{ param_->quantityColors / 2 };
	if (param_->quantityColors % 2 == 1)
	{
		++stepCoefficient;
	}
	unsigned int minColor{ param_->medium - (param_->step * stepCoefficient) };
	for (int i{ 0 }; i < param_->imageHeigth; ++i)
	{
		for (int j{ 0 }; j < param_->imageWidth; ++j)
		{
			inOutImage.at<uchar>(i, j) = minColor + param_->step * inOutImage.at<uchar>(i, j);
		}
	}
}

void GibsModel::setParametrs(IModelParametrs* parametrs)
{
    param_ = dynamic_cast<GibsModelParametrs*>(parametrs);
}

void GibsModel::computeParametrsForObject(IModelParametrs* parametrs, float contrast)
{
	GibsModelParametrs* buferParametsr{ dynamic_cast<GibsModelParametrs*>(parametrs) };
	buferParametsr->medium = param_->medium;
	buferParametsr->medium *= contrast;
	buferParametsr->quantityColors = param_->quantityColors;
	buferParametsr->step = param_->step;
	buferParametsr->propabilityMap = param_->propabilityMap;
	buferParametsr->startFrequencyClasses = param_->startFrequencyClasses;
}

int GibsModel::getMainObjectColor(float contrast)
{
	return static_cast<int>(round(param_->medium * contrast));
}

int GibsModel::getValueFromPropabilityMap(int const firstClass, int const secondClass) const
{
    return param_->propabilityMap[firstClass][secondClass];
}

int GibsModel::generateNewValue(const std::vector<int>& ProbabilityDensity)
{
	int allValue{ std::accumulate(ProbabilityDensity.begin(),ProbabilityDensity.end(),0) };
	std::uniform_int_distribution<> initDist{ 0, static_cast<int>(param_->quantityColors - 1) };
	std::uniform_real_distribution<> dis{ 0.0, 1.0 };
	for (; ;)
	{
		int newValue{ initDist(generator_) };
		double propabilityNewValue{ static_cast<double>(ProbabilityDensity[newValue]) / allValue };
		double conversionPropability{ dis(generator_) };
		if (conversionPropability < propabilityNewValue)
		{
			return newValue;
		}
	}
}

std::vector<int> GibsModel::computeProbabilityDensity1(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity2(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity3(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity4(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity5(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity6(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity7(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity8(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	return startFrequency;
}

std::vector<int> GibsModel::computeProbabilityDensity9(int const x, int const y)
{
	std::vector<int> startFrequency(param_->quantityColors, 0);
	startFrequency[mainImage_.at<uchar>(y + 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y + 1, x));
	startFrequency[mainImage_.at<uchar>(y - 1, x)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y - 1, x));
	startFrequency[mainImage_.at<uchar>(y, x + 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x + 1));
	startFrequency[mainImage_.at<uchar>(y, x - 1)] += getValueFromPropabilityMap(mainImage_.at<uchar>(y, x), mainImage_.at<uchar>(y, x - 1));
	return startFrequency;
}

void GibsModel::generatePart1()
{
	std::vector<int> startFrenqce(computeProbabilityDensity1(0, 0));
	mainImage_.at<uchar>(0, 0) = generateNewValue(startFrenqce);
}

void GibsModel::generatePart2()
{
	for (int i{ 1 }; i < param_->imageWidth - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity2(i, 0));
		mainImage_.at<uchar>(0, i) = generateNewValue(startFrenqce);
	}
}

void GibsModel::generatePart3()
{
	std::vector<int> startFrenqce(computeProbabilityDensity3(param_->imageWidth - 1, 0));
	mainImage_.at<uchar>(0, param_->imageWidth - 1) = generateNewValue(startFrenqce);
}

void GibsModel::generatePart4()
{
	for (int i{ 1 }; i < param_->imageHeigth - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity4(param_->imageWidth - 1, i));
		mainImage_.at<uchar>(i, param_->imageWidth - 1) = generateNewValue(startFrenqce);
	}
}

void GibsModel::generatePart5()
{
	std::vector<int> startFrenqce(computeProbabilityDensity5(param_->imageWidth - 1, param_->imageHeigth - 1));
	mainImage_.at<uchar>(param_->imageHeigth - 1, param_->imageWidth - 1) = generateNewValue(startFrenqce);
}

void GibsModel::generatePart6()
{
	for (int i{ 1 }; i < param_->imageWidth - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity6(i, param_->imageHeigth - 1));
		mainImage_.at<uchar>(param_->imageHeigth - 1, i) = generateNewValue(startFrenqce);
	}
}

void GibsModel::generatePart7()
{
	std::vector<int> startFrenqce(computeProbabilityDensity7(0, param_->imageHeigth - 1));
	mainImage_.at<uchar>(param_->imageHeigth - 1, 0) = generateNewValue(startFrenqce);
}

void GibsModel::generatePart8()
{
	for (int i{ 1 }; i < param_->imageHeigth - 1; ++i)
	{
		std::vector<int> startFrenqce(computeProbabilityDensity8(0, i));
		mainImage_.at<uchar>(i, 0) = generateNewValue(startFrenqce);
	}
}

void GibsModel::generatePart9()
{
	for (int j{ 1 }; j < param_->imageWidth - 1; ++j)
	{
		for (int i{ 1 }; i < param_->imageHeigth - 1; ++i)
		{
			std::vector<int> startFrenqce(computeProbabilityDensity9(j, i));
			mainImage_.at<uchar>(i, j) = generateNewValue(startFrenqce);
		}
	}
}

void GibsModel::initMainImage()
{
	mainImage_ = cv::Mat::zeros(param_->imageHeigth, param_->imageWidth, CV_8UC1);
	std::discrete_distribution<int> initImageDist{ param_->startFrequencyClasses.begin(), param_->startFrequencyClasses.end() };
	for (int i{ 0 }; i < param_->imageHeigth; ++i)
	{
		for (int j{ 0 }; j < param_->imageWidth; ++j)
		{
			mainImage_.at<uchar>(i, j) = initImageDist(generator_);
		}
	}
}
