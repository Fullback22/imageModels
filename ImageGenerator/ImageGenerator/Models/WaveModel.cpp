#include "WaveModel.h"

void WaveModel::generateWaveParams()
{
	std::random_device rd{};
	std::mt19937 gen{};
	std::normal_distribution<float> Rdis{ param_->meanRadius, param_->skoRadius };
	std::normal_distribution<float> ksiDis{ 0.5, param_->skoBrightness/255.0f };
	
	int maxQuantityWave{ param_->imageHeigth * param_->imageWidth };
	int waveThreshold{ (maxQuantityWave / (100  * static_cast<int>(iteration))) * static_cast<int>(param_->distThreshold) };
	size_t quantityWave{ waveParams_.size() };
	while (quantityWave == waveParams_.size())
	for (int i{ 0 }; i < mainImage_.size().height; ++i)
	{
		for (int j{ 0 }; j < mainImage_.size().width; ++j)
		{
			std::uniform_int_distribution<int> dis{ 0, maxQuantityWave };
			if (dis(gen) < waveThreshold)
			{
				waveParams_.push_back(WaveParams{});
				auto activParam = waveParams_.rbegin();
				(*activParam).center = cv::Point(j, i);
				(*activParam).R = Rdis(gen);
				(*activParam).ksi = ksiDis(gen);
			}
		}
	}
}

void WaveModel::generateImage(cv::Mat& inOutImage)
{
	mainImage_ = cv::Mat::zeros(param_->imageHeigth, param_->imageWidth, CV_32FC1) ;
	waveParams_.clear();
	
	float const mu{ 0.1 };
	
	for (size_t t{}; t < iteration; ++t)
	{
		generateWaveParams();
		cv::Mat lastImage{};
		mainImage_.copyTo(lastImage);
		for (int i{ 0 }; i < mainImage_.size().height; ++i)
		{
			for (int j{ 0 }; j < mainImage_.size().width; ++j)
			{
				double secondSummand{ 0.0 };
				int c{ 1 };
				for (int z{ 0 }; z < waveParams_.size(); ++z)
				{
					double ro{ sqrt(pow(waveParams_[z].center.x - j, 2) + pow(waveParams_[z].center.y - i, 2)) };
					double toSqr{ ro / waveParams_[z].R };
					double toExp{ pow(toSqr,2) * -2 };
					double secondSummandnewPart{ exp(toExp) * waveParams_[z].ksi };
					secondSummand += secondSummandnewPart;
					if (secondSummandnewPart > param_->meanBrightness / 255.0)
						c += 1;
				}
				double firstSummand{ std::exp(-mu) };
				double newValue{ lastImage.at<float>(i, j) * firstSummand + secondSummand / c };
				if (newValue > 1.0)
					mainImage_.at<float>(i, j) = newValue - std::floor(newValue);
				else
					mainImage_.at<float>(i, j) = newValue;
			}
		}
	}
	inOutImage = cv::Mat::zeros(param_->imageHeigth, param_->imageWidth, CV_8UC1);
	for (int i{ 0 }; i < mainImage_.size().height; ++i)
	{
		for (int j{ 0 }; j < mainImage_.size().width; ++j)
		{
			inOutImage.at<uchar>(i, j) = static_cast<uchar>(mainImage_.at<float>(i, j) * param_->meanBrightness * 2);
		}
	}
}

void WaveModel::setParametrs(IModelParametrs* parametrs)
{
	param_ = dynamic_cast<WaveModelParametrs*>(parametrs);
}

void WaveModel::computeParametrsForObject(IModelParametrs* parametrs, float contrast)
{
	WaveModelParametrs* buferParametsr{ dynamic_cast<WaveModelParametrs*>(parametrs) };
	buferParametsr->meanBrightness = param_->meanBrightness;
	buferParametsr->meanBrightness *= contrast;
	buferParametsr->skoBrightness = param_->skoBrightness;
	buferParametsr->distThreshold = param_->distThreshold;
	buferParametsr->meanRadius = param_->meanRadius;
	buferParametsr->skoRadius = param_->skoRadius;
}

int WaveModel::getMainObjectColor(float contrast)
{
    return static_cast<int>(round(param_->meanBrightness * contrast));;
}
