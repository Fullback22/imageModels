#include "SimpelTwiceRandomModel.h"

void SimpelTwiceRandomModel::generateImage(cv::Mat& inOutImage)
{
	imageSize.height = param_->imageHeigth;
	imageSize.width = param_->imageWidth;
	
	generateRandomCorrelationCoefficients(param_->sifmaForCorrelationCoeficients);
	generateRandomMean();
	generateRandomStandatrDeviation();
	
	changeMeanInRandomMean(param_->meanBrightness);
	changeMeanInStandatrDeviation(param_->meanStdDeviation);
	
	cv::Mat bufer{ generateMainImage() };
	normolizeImage(bufer);
	bufer.copyTo(inOutImage);
}

void SimpelTwiceRandomModel::setParametrs(IModelParametrs* parametrs)
{
	param_ = dynamic_cast<SimpelTwiceRandomModelParametrs*>(parametrs);
}

void SimpelTwiceRandomModel::computeParametrsForObject(IModelParametrs* parametrs, float contrast)
{
	SimpelTwiceRandomModelParametrs* buferParametsr{ dynamic_cast<SimpelTwiceRandomModelParametrs*>(parametrs) };
	buferParametsr->correlationCoeficients = param_->correlationCoeficients;
	buferParametsr->sifmaForCorrelationCoeficients = param_->sifmaForCorrelationCoeficients;
	buferParametsr->meanBrightness = param_->meanBrightness * contrast;
	buferParametsr->skoBrightness = param_->skoBrightness;
	buferParametsr->meanStdDeviation = param_->meanStdDeviation;
	buferParametsr->skoStdDeviation = param_->skoStdDeviation;
	buferParametsr->skoForMainImage = param_->skoForMainImage;
}

int SimpelTwiceRandomModel::getMainObjectColor(float contrast)
{
	return static_cast<int>(round(param_->meanBrightness * 255.0 * contrast));
}

double SimpelTwiceRandomModel::getSigmaForGaus(double const sigmaForRandomCoeficients)
{
	double r0Sqear{ pow(param_->sifmaForCorrelationCoeficients[0],2) };
	double r1Sqear{ pow(param_->sifmaForCorrelationCoeficients[1],2) };
	double deviatio{ (1 - r0Sqear) * (1 - r1Sqear) * pow(sigmaForRandomCoeficients,2) };
	return std::sqrt(deviatio);
}

cv::Mat SimpelTwiceRandomModel::generateSimpelRandomField(cv::Mat const gausRandomFields)
{
	cv::Mat buferImage{ imageSize, CV_32FC1 };

	buferImage.at<float>(0, 0) = gausRandomFields.at<float>(0, 0);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		buferImage.at<float>(0, i) = param_->correlationCoeficients[0] * buferImage.at<float>(0, i - 1) + gausRandomFields.at<float>(0, i);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		buferImage.at<float>(i, 0) = param_->correlationCoeficients[1] * buferImage.at<float>(i - 1, 0) + gausRandomFields.at<float>(i, 0);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			double rx{ param_->correlationCoeficients[0] * buferImage.at<float>(i, j - 1) };
			double ry{ param_->correlationCoeficients[1] * buferImage.at<float>(i - 1, j) };
			double rxy{ param_->correlationCoeficients[0] * param_->correlationCoeficients[1] * buferImage.at<float>(i - 1, j - 1) };

			buferImage.at<float>(i, j) = rx + ry - rxy + gausRandomFields.at<float>(i, j);
		}
	}
	return buferImage;
}

void SimpelTwiceRandomModel::changeMeanInRandomFields(cv::Mat& inOutputImage, float const newMean)
{
	for (int i{ 0 }; i < inOutputImage.size().height; ++i)
	{
		for (int j{ 0 }; j < inOutputImage.size().width; ++j)
		{
			inOutputImage.at<float>(i, j) = inOutputImage.at<float>(i, j) + newMean;
		}
	}
}

void SimpelTwiceRandomModel::generateGausField(cv::Mat& gausFields, const double sigmaForRandomCoeficient)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	double sigma{ getSigmaForGaus(sigmaForRandomCoeficient) };
	cv::Mat buferImage{  };
	std::normal_distribution<float> dist(0, sigma);

	gausFields = cv::Mat{ imageSize, CV_32FC1 };
	for (int i{ 0 }; i < imageSize.height; ++i)
	{
		for (int j{ 0 }; j < imageSize.width; ++j)
		{
			gausFields.at<float>(i, j) = dist(gen);
		}
	}
}

void SimpelTwiceRandomModel::generateRandomCorrelationCoefficients(const std::vector<double>& sigmaForCorrelationCoeficient)
{	
	for (const auto& sigma: sigmaForCorrelationCoeficient)
	{
		cv::Mat gausField{};
		generateGausField(gausField, sigma);
		cv::Mat bufer{ generateSimpelRandomField(gausField) };
		randomCorrelationCoefficients.push_back(bufer);
	}
}

void SimpelTwiceRandomModel::generateRandomMean()
{
	cv::Mat gausField{};
	generateGausField(gausField, param_->skoBrightness);
	randomMean = generateSimpelRandomField(gausField);
}

void SimpelTwiceRandomModel::generateRandomStandatrDeviation()
{
	cv::Mat gausField{};
	generateGausField(gausField, param_->skoStdDeviation);
	randomStandatrDeviation = generateSimpelRandomField(gausField);
}

void SimpelTwiceRandomModel::changeMeanInRandomMean(float const newMean)
{
	changeMeanInRandomFields(randomMean, newMean);
}

void SimpelTwiceRandomModel::changeMeanInStandatrDeviation(float const newMean)
{
	changeMeanInRandomFields(randomStandatrDeviation, newMean);
}

cv::Mat SimpelTwiceRandomModel::normolizeImage(cv::Mat& inOutputImage)
{
	//cv::normalize(inOutputImage, inOutputImage, 1.0, 0.0, cv::NORM_MINMAX);
	cv::convertScaleAbs(inOutputImage, inOutputImage, 255.0);
	return inOutputImage;
}

std::vector<cv::Mat> SimpelTwiceRandomModel::getRandomCorrelationCoefficients() const
{
	return randomCorrelationCoefficients;
}

cv::Mat SimpelTwiceRandomModel::generateMainImage()
{
	cv::Mat buferImage{ imageSize, CV_32FC1 };
	cv::Mat gausField{};
	generateGausField(gausField, param_->skoForMainImage);

	cv::Mat buf12{ randomMean };

	buferImage.at<float>(0, 0) = randomMean.at<float>(0, 0) + randomStandatrDeviation.at<float>(0, 0) * gausField.at<float>(0, 0);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		float rx{ randomCorrelationCoefficients[0].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		float rxy{ randomCorrelationCoefficients[0].at<float>(0, i) * randomCorrelationCoefficients[1].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		buferImage.at<float>(0, i) = randomMean.at<float>(0, i) + rx - rxy + randomStandatrDeviation.at<float>(0, i) * gausField.at<float>(0, i);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		float ry{ randomCorrelationCoefficients[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		float rxy{ randomCorrelationCoefficients[0].at<float>(i, 0) * randomCorrelationCoefficients[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		buferImage.at<float>(i, 0) = randomMean.at<float>(i, 0) + ry - rxy + randomStandatrDeviation.at<float>(i, 0) * gausField.at<float>(i, 0);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			float rx{ randomCorrelationCoefficients[0].at<float>(i, j) * buferImage.at<float>(i, j - 1) };
			float ry{ randomCorrelationCoefficients[1].at<float>(i, j) * buferImage.at<float>(i - 1, j) };
			float rxy{ randomCorrelationCoefficients[0].at<float>(i, j) * randomCorrelationCoefficients[1].at<float>(i, j) * buferImage.at<float>(i - 1, j - 1) };

			buferImage.at<float>(i, j) = randomMean.at<float>(i, j) + rx + ry - rxy + randomStandatrDeviation.at<float>(i, j) * gausField.at<float>(i, j);
		}
	}

	return buferImage;
}
