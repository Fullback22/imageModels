#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

class IImageModel
{
public:
	virtual ~IImageModel() {};
	virtual void generateImage(cv::Mat& inOutImage) = 0;
	virtual void setParametrs() = 0;
};

