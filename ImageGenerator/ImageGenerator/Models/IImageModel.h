#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "Parametrs/IModelParametrs.h"

class IImageModel
{
public:
	virtual ~IImageModel() {};
	virtual void generateImage(cv::Mat& inOutImage) = 0;
	virtual void setParametrs(IModelParametrs* parametsr) = 0;
	virtual void computeParametrsForObject(IModelParametrs* parametsr, float contrast) = 0;
	virtual int getMainObjectColor(float contrast) = 0;
};

