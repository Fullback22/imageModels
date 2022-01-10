#include "HeterogeneousTwiceRandomModel.h"

float HeterogeneousTwiceRandomModel::quantization(float const value, float const gama)
{
	return (round(value * gama)) / gama;
}

cv::Mat HeterogeneousTwiceRandomModel::generateSimpelRandomField(cv::Mat const gausRandomFields, float const gama)
{
	cv::Mat buferImage{ imageSize, CV_32FC1 };
	float newValue{ gausRandomFields.at<float>(0, 0) };
	buferImage.at<float>(0, 0) = quantization(newValue, gama);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		newValue = correlationCoefficients[0] * buferImage.at<float>(0, i - 1) + gausRandomFields.at<float>(0, i);
		buferImage.at<float>(0, i) = quantization(newValue, gama);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		newValue = correlationCoefficients[1] * buferImage.at<float>(i - 1, 0) + gausRandomFields.at<float>(i, 0);
		buferImage.at<float>(i, 0) = quantization(newValue, gama);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			float rx{ correlationCoefficients[0] * buferImage.at<float>(i, j - 1) };
			float ry{ correlationCoefficients[1] * buferImage.at<float>(i - 1, j) };
			float rxy{ correlationCoefficients[0] * correlationCoefficients[1] * buferImage.at<float>(i - 1, j - 1) };
			newValue = rx + ry - rxy + gausRandomFields.at<float>(i, j);

			buferImage.at<float>(i, j) = quantization(newValue, gama);
		}
	}
	return buferImage;
}

HeterogeneousTwiceRandomModel::HeterogeneousTwiceRandomModel(cv::Size* const imageSize, std::vector<float>* correlationCoefficients):
	SimpelTwiceRandomModel(imageSize, correlationCoefficients)
{
}

void HeterogeneousTwiceRandomModel::generateRandomCorrelationCoefficients(float const gama)
{
	for (int i{ 0 }; i < gausRandomFields.size(); ++i)
	{
		cv::Mat bufer{ generateSimpelRandomField(gausRandomFields[i], gama) };
		randomCorrelationCoefficients.push_back(bufer);
	}
}

void HeterogeneousTwiceRandomModel::generateRandomMean(float const gama)
{
	randomMean = generateSimpelRandomField(gausRandomFields[0], gama);
}

void HeterogeneousTwiceRandomModel::generateRandomStandatrDeviation(float const gama)
{
	randomStandatrDeviation = generateSimpelRandomField(gausRandomFields[0], gama);
}

cv::Mat HeterogeneousTwiceRandomModel::generateMainImage(float const gama)
{
	cv::Mat buferImage{ imageSize, CV_32FC1 };
	cv::Mat asd{ gausRandomFields[0] };
	float newValue{ randomMean.at<float>(0, 0) + randomStandatrDeviation.at<float>(0, 0) * gausRandomFields[0].at<float>(0, 0) };

	buferImage.at<float>(0, 0) = quantization(newValue, gama);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		float rx{ randomCorrelationCoefficients[0].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		float rxy{ randomCorrelationCoefficients[0].at<float>(0, i) * randomCorrelationCoefficients[1].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		newValue = randomMean.at<float>(0, i) + rx - rxy + randomStandatrDeviation.at<float>(0, i) * gausRandomFields[0].at<float>(0, i);

		buferImage.at<float>(0, i) = quantization(newValue, gama);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		float ry{ randomCorrelationCoefficients[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		float rxy{ randomCorrelationCoefficients[0].at<float>(i, 0) * randomCorrelationCoefficients[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		newValue = randomMean.at<float>(i, 0) + ry - rxy + randomStandatrDeviation.at<float>(i, 0) * gausRandomFields[0].at<float>(i, 0);

		buferImage.at<float>(i, 0) = quantization(newValue, gama);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			float rx{ randomCorrelationCoefficients[0].at<float>(i, j) * buferImage.at<float>(i, j - 1) };
			float ry{ randomCorrelationCoefficients[1].at<float>(i, j) * buferImage.at<float>(i - 1, j) };
			float rxy{ randomCorrelationCoefficients[0].at<float>(i, j) * randomCorrelationCoefficients[1].at<float>(i, j) * buferImage.at<float>(i - 1, j - 1) };
			newValue = randomMean.at<float>(i, j) + rx + ry - rxy + randomStandatrDeviation.at<float>(i, j) * gausRandomFields[0].at<float>(i, j);

			buferImage.at<float>(i, j) = quantization(newValue, gama);
		}
	}
	return buferImage;
}

cv::Mat HeterogeneousTwiceRandomModel::generateStandartMainImage()
{
	std::vector<float> sigmaForRandomCoeficients{ 0.2, 0.2 };
	for (auto& sko : sigmaForRandomCoeficients)
	{
		sko = sigmaForGaus(sko);
	}
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomCorrelationCoefficients(30);
	sigmaForRandomCoeficients.clear();
	sigmaForRandomCoeficients.push_back(1);
	sigmaForRandomCoeficients[0] = sigmaForGaus(sigmaForRandomCoeficients[0]);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomMean(30);
	generateRandomStandatrDeviation(30);
	changeMeanInRandomMean(0.9);
	changeMeanInStandatrDeviation(0.9);
	sigmaForRandomCoeficients[0] = 1;
	sigmaForRandomCoeficients[0] = sigmaForGaus(sigmaForRandomCoeficients[0]);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	cv::Mat bufer{ generateMainImage(0.5) };
	normolizeImage(bufer);
	return bufer;
}

cv::Mat HeterogeneousTwiceRandomModel::generateStandartMainImage(std::vector<float>* const sigmaForRandomCorrelationCoeficients, 
																float const sigmaForRandomMean, 
																float const sigmaForRandomStdDeviation, 
																float const meanForRandomMean, 
																float const meanForRandomStdDeviation, 
																float const sigmaForMainImage, 
																float const quantizationGammaForCorrelationCoeficients, 
																float const quantizationGammaForMeanAndStdDeviation, 
																float const quantizationGammaForMainImage, 
																bool const normolizeImage_)
{
	std::vector<float> sigmaForRandomCoeficients{ *sigmaForRandomCorrelationCoeficients };
	for (auto& sko : sigmaForRandomCoeficients)
	{
		sko = sigmaForGaus(sko);
	}
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomCorrelationCoefficients(quantizationGammaForCorrelationCoeficients);
	sigmaForRandomCoeficients.clear();

	sigmaForRandomCoeficients.push_back(sigmaForRandomMean);
	sigmaForRandomCoeficients[0] = sigmaForGaus(sigmaForRandomCoeficients[0]);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomMean(quantizationGammaForMeanAndStdDeviation);

	sigmaForRandomCoeficients[0] = sigmaForRandomStdDeviation;
	sigmaForRandomCoeficients[0] = sigmaForGaus(sigmaForRandomCoeficients[0]);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	generateRandomStandatrDeviation(quantizationGammaForMeanAndStdDeviation);

	changeMeanInRandomMean(meanForRandomMean);
	changeMeanInStandatrDeviation(meanForRandomStdDeviation);

	sigmaForRandomCoeficients[0] = sigmaForMainImage;
	sigmaForRandomCoeficients[0] = sigmaForGaus(sigmaForRandomCoeficients[0]);
	generateGausRandomFields(&sigmaForRandomCoeficients);
	cv::Mat bufer{ generateMainImage(quantizationGammaForMainImage) };
	if (normolizeImage_)
		normolizeImage(bufer);
	return bufer;
}
