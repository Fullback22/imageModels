#include "MarkovFields.h"

int MarkovFields::getNewValue(const std::vector<int>& frequncys)
{
	std::discrete_distribution<int> initImageDist(frequncys.begin(), frequncys.end());
	return initImageDist(generator_);
}

MarkovFields::MarkovFields()
{
}

MarkovFields::MarkovFields(const cv::Size& imageSize):
	imageSize_(imageSize)
{
}

MarkovFields& MarkovFields::operator=(const MarkovFields& drop)
{
	imageSize_ = drop.imageSize_;
	generator_ = drop.generator_;
	conditionalTransitions_.assign(drop.conditionalTransitions_.begin(), drop.conditionalTransitions_.end());
	return *this;
}

void MarkovFields::initConditionalTransitions(int const transitionsStep)
{
	for (int i{ }; i < 255; ++i)
	{
		conditionalTransitions_.push_back(std::vector<int>(255, 0));
		int transitionsFreqences{ 255 };
		for (int j{ i }; j < 255 && transitionsFreqences > 0; ++j)
		{
			conditionalTransitions_[i][j] = transitionsFreqences;
			transitionsFreqences -= transitionsStep;
		}
		transitionsFreqences = 255;
		for (int j{ i }; j >= 0 && transitionsFreqences > 0; --j)
		{
			conditionalTransitions_[i][j] = transitionsFreqences;
			transitionsFreqences -= transitionsStep;
		}
	}
}

void MarkovFields::setConditionalTransitions(const std::vector<std::vector<int>>& conditionalTransitions)
{
	conditionalTransitions_.assign(conditionalTransitions.begin(), conditionalTransitions.end());
}

cv::Mat MarkovFields::generateStandartMainImage()
{
	cv::Mat mainImage{ imageSize_, CV_8UC1 };
	std::uniform_int_distribution<> initDist{ 0, static_cast<int>(conditionalTransitions_.size()) - 1 };
	mainImage.at<uchar>(0, 0) = initDist(generator_);

	for (int i{ 1 }; i < imageSize_.width; ++i)
	{
		mainImage.at<uchar>(0, i) = getNewValue(conditionalTransitions_[mainImage.at<uchar>(0, i - 1)]);
	}

	for (int i{ 1 }; i < imageSize_.height; ++i)
	{
		mainImage.at<uchar>(i, 0) = getNewValue(conditionalTransitions_[mainImage.at<uchar>(i - 1, 0)]);
	}

	for (int i{ 1 }; i < imageSize_.height; ++i)
	{
		for (int j{ 1 }; j < imageSize_.width; ++j)
		{
			mainImage.at<uchar>(i, j) = getNewValue(conditionalTransitions_[mainImage.at<uchar>(i-1, j)]);
		}
	}
	return mainImage;
}


