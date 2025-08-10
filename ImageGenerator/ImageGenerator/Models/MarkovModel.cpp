#include "MarkovModel.h"

unsigned int MarkovModel::getNewValue(const std::vector<unsigned int>& frequncys)
{
	std::discrete_distribution<unsigned int> initImageDist(frequncys.begin(), frequncys.end());
	return initImageDist(generator_);
}

void MarkovModel::generateImage(cv::Mat& inOutImage)
{
	inOutImage = cv::Mat(param_->imageHeigth, param_->imageWidth, CV_8UC1);
	std::uniform_int_distribution<> initDist{ 0, static_cast<int>(param_->conditionalTransitions.size()) - 1 };
	inOutImage.at<uchar>(0, 0) = initDist(generator_);

	for (int i{ 1 }; i < param_->imageWidth; ++i)
	{
		inOutImage.at<uchar>(0, i) = getNewValue(param_->conditionalTransitions[inOutImage.at<uchar>(0, i - 1)]);
	}

	for (int i{ 1 }; i < param_->imageHeigth; ++i)
	{
		inOutImage.at<uchar>(i, 0) = getNewValue(param_->conditionalTransitions[inOutImage.at<uchar>(i - 1, 0)]);
	}

	for (int i{ 1 }; i < param_->imageHeigth; ++i)
	{
		for (int j{ 1 }; j < param_->imageWidth; ++j)
		{
			inOutImage.at<uchar>(i, j) = getNewValue(param_->conditionalTransitions[inOutImage.at<uchar>(i - 1, j)]);
		}
	}

	unsigned int stepCoefficient{ param_->quantityColors / 2 };
	if (param_->quantityColors % 2 == 1)
	{
		++stepCoefficient;
	}
	unsigned int minColor{param_->medium - (param_->step * stepCoefficient) };
	for (int i{ 0 }; i < param_->imageHeigth; ++i)
	{
		for (int j{ 0 }; j < param_->imageWidth; ++j)
		{
			inOutImage.at<uchar>(i, j) = minColor + param_->step * inOutImage.at<uchar>(i, j);
		}
	}
}

void MarkovModel::setParametrs(IModelParametrs* parametrs)
{
	param_ = dynamic_cast<MarkovModelParametrs*>(parametrs);
}

void MarkovModel::computeParametrsForObject(IModelParametrs* parametrs, float contrast)
{
	MarkovModelParametrs* buferParametsr{ dynamic_cast<MarkovModelParametrs*>(parametrs) };
	buferParametsr->medium = param_->medium;
	buferParametsr->medium *= contrast;
	buferParametsr->quantityColors = param_->quantityColors;
	buferParametsr->step = param_->step;
	buferParametsr->conditionalTransitions = param_->conditionalTransitions;

}

int MarkovModel::getMainObjectColor(float contrast)
{
	return static_cast<int>(round(param_->medium * contrast));
}
