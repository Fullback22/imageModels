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

cv::Mat HeterogeneousTwiceRandomModel::generateStandartMainImage(std::vector<float>* const sigmaForRandomCorrelationCoeficients, float const sigmaForRandomMean, float const sigmaForRandomStdDeviation, float const meanForRandomMean, float const meanForRandomStdDeviation, float const sigmaForMainImage, float const quantizationGammaForCorrelationCoeficients, float const quantizationGammaForMeanAndStdDeviation, float const quantizationGammaForMainImage, bool const normolizeImage)
{
	cv::Mat backgroundImage{ background.generateStandartMainImage(sigmaForRandomCorrelationCoeficients, 
		sigmaForRandomMean, 
		sigmaForRandomStdDeviation, 
		meanForRandomMean, 
		meanForRandomStdDeviation, 
		sigmaForMainImage) };

	cv::Mat arearImage{ arears.generateStandartMainImage(sigmaForRandomCorrelationCoeficients,
		sigmaForRandomMean,
		sigmaForRandomStdDeviation,
		meanForRandomMean,
		meanForRandomStdDeviation,
		sigmaForMainImage,
		quantizationGammaForCorrelationCoeficients,
		quantizationGammaForMeanAndStdDeviation,
		quantizationGammaForMainImage) };

	std::vector<cv::Mat> arearImage1{ arears.getRandomCorrelationCoefficients() };
	cv::Mat bufer{ arearImage1[0] };
	backgroundImage += arearImage1[0];
	cv::normalize(backgroundImage, backgroundImage, 1.0, 0.0, cv::NORM_MINMAX);
	return backgroundImage;
}
