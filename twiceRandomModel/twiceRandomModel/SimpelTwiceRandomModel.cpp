#include "SimpelTwiceRandomModel.h"

float SimpelTwiceRandomModel::sigmaForGaus(float const sigmaForRandomCoeficients)
{
	float r0Sqear{ correlationCoefficients[0] * correlationCoefficients[0] };
	float r1Sqear{ correlationCoefficients[1] * correlationCoefficients[1] };
	float deviatio{ (1 - r0Sqear) * (1 - r1Sqear) * sigmaForRandomCoeficients * sigmaForRandomCoeficients };
	return std::sqrt(deviatio);
}

SimpelTwiceRandomModel::SimpelTwiceRandomModel(cv::Size* const imageSize_, int quantityCorrelationCoefficients_):
	imageSize{ *imageSize_ },
	quantityCorrelationCoefficients{quantityCorrelationCoefficients_}
{
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
