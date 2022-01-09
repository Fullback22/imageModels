#include "iostream"

#include "SimpelTwiceRandomModel.h"

int main()
{
	std::vector<float> correletionCoefficient(2, 0.99);
	cv::Size imageSize{ 600, 400 };
	SimpelTwiceRandomModel firstModel{ &imageSize, &correletionCoefficient };

	std::vector<float> sigmaForRandomCorrelationCoeficients{ 0.3, 0.3 };
	float const sigmaForRandomMean{ 0.2 };
	float const sigmaForRandomStdDeviation{ 0.2 };
	float const meanForRandomMean{ 0.9 };
	float const meanForRandomStdDeviation{ 0.8 };
	float const sigmaForMainImage{ 0.3 };
	bool const normolizeImage{ true };

	cv::Mat qwe{ firstModel.generateStandartMainImage(&sigmaForRandomCorrelationCoeficients,
														sigmaForRandomMean,
														sigmaForRandomStdDeviation,
														meanForRandomMean,
														meanForRandomStdDeviation,
														sigmaForMainImage,
														normolizeImage) };
	std::vector<cv::Mat> randomCorrelationCoeficients{ firstModel.getRandomCorrelationCoefficients() };
	for (auto& image : randomCorrelationCoeficients)
	{
		cv::normalize(image, image, 1.0, 0.0, cv::NORM_MINMAX);

	}
	cv::imshow("Correlation0", randomCorrelationCoeficients[0]);
	cv::imshow("Correlation1", randomCorrelationCoeficients[1]);
	cv::imshow("image", qwe);
	cv::waitKey();
	return 0;
}