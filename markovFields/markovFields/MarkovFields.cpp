#include "MarkovFields.h"

int MarkovFields::getNewValue(std::vector<int>* frequncys)
{
	std::discrete_distribution<int> initImageDist(frequncys->begin(), frequncys->end());
	return initImageDist(gen);
}

MarkovFields::MarkovFields(cv::Size const* imageSize_):
	imageSize(*imageSize_),
	gen{rd()}
{
}

void MarkovFields::initConditionalTransitions(int const transitionsStep)
{
	for (int i{ 0 }; i < 255; ++i)
	{
		conditionalTransitions.push_back(std::vector<int>(255, 0));
		int transitionsFreqences{ 255 };
		for (int j{ i }; j < 255 && transitionsFreqences > 0; ++j)
		{
			conditionalTransitions[i][j] = transitionsFreqences;
			transitionsFreqences -= transitionsStep;
		}
		transitionsFreqences = 255;
		for (int j{ i }; j >= 0 && transitionsFreqences > 0; --j)
		{
			conditionalTransitions[i][j] = transitionsFreqences;
			transitionsFreqences -= transitionsStep;
		}
	}
}

void MarkovFields::setConditionalTransitions(std::vector<std::vector<int>>* conditionalTransitions_)
{
	conditionalTransitions.assign(conditionalTransitions_->begin(), conditionalTransitions_->end());
}

cv::Mat MarkovFields::generateStandartMainImage()
{
	cv::Mat mainImage{ imageSize, CV_8UC1 };
	std::uniform_int_distribution<> initDist{ 0, 255 };
	mainImage.at<uchar>(0, 0) = initDist(gen);

	for (int i{ 1 }; i < imageSize.width; ++i)
	{
		mainImage.at<uchar>(0, i) = getNewValue(&conditionalTransitions[mainImage.at<uchar>(0, i - 1)]);
	}

	for (int i{ 1 }; i < imageSize.height; ++i)
	{
		mainImage.at<uchar>(i, 0) = getNewValue(&conditionalTransitions[mainImage.at<uchar>(i - 1, 0)]);
	}

	for (int i{ 1 }; i < imageSize.height; ++i)
	{
		for (int j{ 1 }; j < imageSize.width; ++j)
		{
			mainImage.at<uchar>(i, j) = getNewValue(&conditionalTransitions[mainImage.at<uchar>(i-1, j)]);
		}
	}
	return mainImage;
}


