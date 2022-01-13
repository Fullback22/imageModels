#include "HeterogeneousTwiceRandomModel.h"

HeterogeneousTwiceRandomModel::HeterogeneousTwiceRandomModel(cv::Size* const imageSize, std::vector<float>* correlationCoefficients):
	background{imageSize, correlationCoefficients},
	arears{ imageSize, correlationCoefficients }
{
}

cv::Mat HeterogeneousTwiceRandomModel::generateStandartMainImage()
{
	cv::Mat backgroundImage{ background.generateStandartMainImage() };
	cv::Mat arearImage{ arears.generateStandartMainImage() };
	std::vector<cv::Mat> arearImage1{ arears.getRandomCorrelationCoefficients() };
	cv::Mat bufer{ arearImage1[0] };
	backgroundImage += arearImage1[0];
	cv::normalize(backgroundImage, backgroundImage, 1.0, 0.0, cv::NORM_MINMAX);
	return backgroundImage;
}
