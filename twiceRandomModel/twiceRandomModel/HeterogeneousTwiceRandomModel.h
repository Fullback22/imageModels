#pragma once
#include "SimpelTwiceRandomModel.h"
#include "HomogeneousArearsTwiceRandomModel.h"

class HeterogeneousTwiceRandomModel
{
	SimpelTwiceRandomModel background;
	HomogeneousArearsTwiceRandomModel arears;
	
public:
	HeterogeneousTwiceRandomModel(cv::Size* const imageSize, std::vector<float>* correlationCoefficients);
	cv::Mat generateStandartMainImage();
	cv::Mat generateStandartMainImage(std::vector<float>* const sigmaForRandomCorrelationCoeficients,
                                    float const sigmaForRandomMean,
                                    float const sigmaForRandomStdDeviation,
                                    float const meanForRandomMean,
                                    float const meanForRandomStdDeviation,
                                    float const sigmaForMainImage,
                                    float const quantizationGammaForCorrelationCoeficients,
                                    float const quantizationGammaForMeanAndStdDeviation,
                                    float const quantizationGammaForMainImage,
                                    bool const normolizeImage = true);

};

