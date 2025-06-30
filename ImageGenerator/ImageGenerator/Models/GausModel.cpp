#include "GausModel.h"

void GausModel::generateImage(cv::Mat& inOutImage)
{
	std::random_device rd{};
	std::mt19937 generator{ rd() };
	std::normal_distribution<float> dist(param_->medium, param_->sko);
	inOutImage = cv::Mat(param_->imageHeigth, param_->imageWidth, CV_8UC1);
	for (int i{ 0 }; i < param_->imageWidth * param_->imageHeigth; ++i)
	{
		float val = dist(generator);
		if (val > 255.0)
		{
			val = 255.0;
		}
		else if (val < 0.0)
		{
			val = 0.0;
		}
		inOutImage.data[i] = static_cast<unsigned char>(val);
	}
}

void GausModel::setParametrs(IModelParametrs* parametrs)
{
	param_ = dynamic_cast<GausModelParametrs*>(parametrs);
}
