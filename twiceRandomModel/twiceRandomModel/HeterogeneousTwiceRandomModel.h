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

};

