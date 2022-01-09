#include "SimpelTwiceRandomModel.h"

float SimpelTwiceRandomModel::sigmaForGaus(float const sigmaForRandomCoeficients)
{
	float r0Sqear{ correlationCoefficients[0] * correlationCoefficients[0] };
	float r1Sqear{ correlationCoefficients[1] * correlationCoefficients[1] };
	float deviatio{ (1 - r0Sqear) * (1 - r1Sqear) * sigmaForRandomCoeficients * sigmaForRandomCoeficients };
	return std::sqrt(deviatio);
}

SimpelTwiceRandomModel::SimpelTwiceRandomModel(cv::Size* const imageSize_, std::vector<float>* correlationCoefficients_):
	imageSize{ *imageSize_ }
{
	correlationCoefficients.assign(correlationCoefficients_->begin(), correlationCoefficients_->end());
}

void SimpelTwiceRandomModel::generateGausRandomFields(std::vector<float>* const sigmaForRandomCoeficients)
{
	gausRandomFields.clear();
	for (int z{ 0 }; z < sigmaForRandomCoeficients->size(); ++z)
	{
		float SKO{ sigmaForGaus((*sigmaForRandomCoeficients)[z]) };
		cv::Mat buferImage{ imageSize, CV_32FC1 };
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::normal_distribution<float> dist(0, SKO);
		for (int i{ 0 }; i < imageSize.height; ++i)
		{
			for (int j{ 0 }; j < imageSize.width; ++j)
			{
				buferImage.at<float>(i, j) = dist(gen);
			}
		}
		gausRandomFields.push_back(buferImage);
	}
}

void SimpelTwiceRandomModel::generateRandomCorrelationCoefficients()
{
	for (int i{ 0 }; i < gausRandomFields.size(); ++i)
	{
		cv::Mat bufer{ generateSimpelRandomField(gausRandomFields[i]) };
		randomCorrelationCoefficients.push_back(bufer);
	}
}

void SimpelTwiceRandomModel::generateRandomMean()
{
	randomMean = generateSimpelRandomField(gausRandomFields[0]);
}

void SimpelTwiceRandomModel::generateRandomStandatrDeviation()
{
	randomStandatrDeviation = generateSimpelRandomField(gausRandomFields[0]);
}

void SimpelTwiceRandomModel::changeMeanInRandomMean(float const newMean)
{
	changeMeanInRandomFields(randomMean, newMean);
}

void SimpelTwiceRandomModel::changeMeanInStandatrDeviation(float const newMean)
{
	changeMeanInRandomFields(randomStandatrDeviation, newMean);
}

cv::Mat SimpelTwiceRandomModel::generateMainImage()
{
	cv::Mat buferImage{ imageSize, CV_32FC1 };

	buferImage.at<float>(0, 0) = randomMean.at<float>(0, 0) + randomStandatrDeviation.at<float>(0, 0) * gausRandomFields[0].at<float>(0, 0);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		float rx{ randomCorrelationCoefficients[0].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		float rxy{ randomCorrelationCoefficients[0].at<float>(0, i) * randomCorrelationCoefficients[1].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		buferImage.at<float>(0, i) = randomMean.at<float>(0, i) + rx - rxy + randomStandatrDeviation.at<float>(0, i) * gausRandomFields[0].at<float>(0, i);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		float ry{ randomCorrelationCoefficients[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		float rxy{ randomCorrelationCoefficients[0].at<float>(i, 0) * randomCorrelationCoefficients[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		buferImage.at<float>(i, 0) = randomMean.at<float>(i, 0) + ry - rxy + randomStandatrDeviation.at<float>(i, 0) * gausRandomFields[0].at<float>(i, 0);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			float rx{ randomCorrelationCoefficients[0].at<float>(i, j) * buferImage.at<float>(i, j - 1) };
			float ry{ randomCorrelationCoefficients[1].at<float>(i, j) * buferImage.at<float>(i - 1, j) };
			float rxy{ randomCorrelationCoefficients[0].at<float>(i, j) * randomCorrelationCoefficients[1].at<float>(i, j) * buferImage.at<float>(i - 1, j - 1) };

			buferImage.at<float>(i, j) = randomMean.at<float>(i, j) + rx + ry - rxy + randomStandatrDeviation.at<float>(i, j) * gausRandomFields[0].at<float>(i, j);
		}
	}

	return buferImage;
}

cv::Mat SimpelTwiceRandomModel::generateStandartMainImage()
{
	std::vector<float> sigmaForRandomCoeficients{ 0.2, 0.2 };
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomCorrelationCoefficients();
	sigmaForRandomCoeficients.clear();
	sigmaForRandomCoeficients.push_back(0.2);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomMean();
	generateRandomStandatrDeviation();
	changeMeanInRandomMean(0.8);
	changeMeanInStandatrDeviation(0.8);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	cv::Mat bufer{ generateMainImage() };
	normolizeImage(bufer);
	return bufer;
}

cv::Mat SimpelTwiceRandomModel::generateStandartMainImage(std::vector<float>* const sigmaForRandomCorrelationCoeficients, 
															float const sigmaForRandomMean, 
															float const sigmaForRandomStdDeviation, 
															float const meanForRandomMean, 
															float const meanForRandomStdDeviation, 
															float const sigmaForMainImage, 
															bool const normolizeImage_)
{
	std::vector<float> sigmaForRandomCoeficients{ 0.2, 0.2 };
	generateGausRandomFields(sigmaForRandomCorrelationCoeficients);
	generateRandomCorrelationCoefficients();
	sigmaForRandomCoeficients.clear();
	sigmaForRandomCoeficients.push_back(sigmaForRandomMean);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomMean();
	sigmaForRandomCoeficients[0] = sigmaForRandomStdDeviation;
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomStandatrDeviation();
	changeMeanInRandomMean(meanForRandomMean);
	changeMeanInStandatrDeviation(meanForRandomStdDeviation);
	sigmaForRandomCoeficients[0] = sigmaForMainImage;
	generateGausRandomFields(&sigmaForRandomCoeficients);
	cv::Mat bufer{ generateMainImage() };
	if(normolizeImage_)
		normolizeImage(bufer);
	return bufer;
}

cv::Mat SimpelTwiceRandomModel::normolizeImage(cv::Mat& inOutputImage)
{
	cv::normalize(inOutputImage, inOutputImage, 1.0, 0.0, cv::NORM_MINMAX);
	return inOutputImage;
}

std::vector<cv::Mat> SimpelTwiceRandomModel::getRandomCorrelationCoefficients() const
{
	return randomCorrelationCoefficients;
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

cv::Mat SimpelTwiceRandomModel::generateSimpelRandomField(cv::Mat const gausRandomFields)
{
	cv::Mat buferImage{ imageSize, CV_32FC1 };

	buferImage.at<float>(0, 0) = gausRandomFields.at<float>(0, 0);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		buferImage.at<float>(0, i) = correlationCoefficients[0] * buferImage.at<float>(0, i - 1) + gausRandomFields.at<float>(0, i);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		buferImage.at<float>(i, 0) = correlationCoefficients[1] * buferImage.at<float>(i - 1, 0) + gausRandomFields.at<float>(i, 0);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			float rx{ correlationCoefficients[0] * buferImage.at<float>(i, j - 1) };
			float ry{ correlationCoefficients[1] * buferImage.at<float>(i - 1, j) };
			float rxy{ correlationCoefficients[0] * correlationCoefficients[1] * buferImage.at<float>(i - 1, j - 1) };

			buferImage.at<float>(i, j) = rx + ry - rxy + gausRandomFields.at<float>(i, j);
		}
	}
	return buferImage;

}
