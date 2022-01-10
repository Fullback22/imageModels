#include "iostream"

#include "SimpelTwiceRandomModel.h"
#include "HomogeneousArearsTwiceRandomModel.h"

int main()
{
	std::vector<float> correletionCoefficient(2, 0.90);
	cv::Size imageSize{ 600, 400 };
	SimpelTwiceRandomModel firstModel{ &imageSize, &correletionCoefficient };
	HomogeneousArearsTwiceRandomModel secondModel{ &imageSize, &correletionCoefficient };

	std::vector<float> sigmaForRandomCorrelationCoeficients{ 0.2, 0.2 };
	float const sigmaForRandomMean{ 1 };
	float const sigmaForRandomStdDeviation{ 1 };
	float const meanForRandomMean{ 0.0 };
	float const meanForRandomStdDeviation{ 0.9 };
	float const sigmaForMainImage{ 0.3 };
	float const quantizationGammaForCorrelationCoeficients{ 3.2 };
	float const quantizationGammaForMeanAndStdDeviation{ 30 };
	float const quantizationGammaForMainImage{ 1.8 };
	bool const normolizeImage{ true };

	/*cv::Mat qwe{ firstModel.generateStandartMainImage(&sigmaForRandomCorrelationCoeficients,
														sigmaForRandomMean,
														sigmaForRandomStdDeviation,
														meanForRandomMean,
														meanForRandomStdDeviation,
														sigmaForMainImage,
														normolizeImage) };*/

	cv::Mat qwe{ secondModel.generateStandartMainImage(&sigmaForRandomCorrelationCoeficients,
														sigmaForRandomMean,
														sigmaForRandomStdDeviation,
														meanForRandomMean,
														meanForRandomStdDeviation,
														sigmaForMainImage,
														quantizationGammaForCorrelationCoeficients,
														quantizationGammaForMeanAndStdDeviation,
														quantizationGammaForMainImage,
														normolizeImage) }; 

	std::vector<cv::Mat> randomCorrelationCoeficients{ secondModel.getRandomCorrelationCoefficients() };
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