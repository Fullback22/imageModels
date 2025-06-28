#include "iostream"

#include "SimpelTwiceRandomModel.h"
#include "HomogeneousArearsTwiceRandomModel.h"
#include "HeterogeneousTwiceRandomModel.h"

int main()
{
	size_t quantityImage{ 108 };
	size_t startNumber{ 0 };

	std::vector<int> imageWidth{ 640, 800, 960, 1024, 1280, 1280, 1600, 1920, 2048 };
	std::vector<int> imageHeigth{ 480, 600, 540, 600, 720, 1024, 900, 1080, 1080 };
	int quantityOfSize{ static_cast<int>(imageHeigth.size()) };
	std::uniform_int_distribution<> imageSizeDistr{ 0, quantityOfSize - 1 };
	std::uniform_real_distribution<float> correletionCoefficientDistr{ 0.7, 0.84 };
	std::uniform_real_distribution<float> sigmaForRandomCorrelationCoeficientsDistr{ 0.1, 0.13 };
	std::uniform_real_distribution<float> sigmaForRandomMeanDistr{ 0.02, 0.1 };
	std::uniform_real_distribution<float> sigmaForRandomStdDeviationDistr{ 0.02, 0.1 };
	std::uniform_real_distribution<float> meanForRandomMeanDistr{ 0.2, 0.9 };
	std::uniform_real_distribution<float> meanForRandomStdDeviationDistr{ 0.1, 0.8 };
	std::uniform_real_distribution<float> sigmaForMainImageDistr{ 0.02, 0.3 };
	std::uniform_real_distribution<float> quantizationGammaForCorrelationCoeficientsDistr{ 2.5, 4.0 };
	std::uniform_int_distribution<> quantizationGammaForMeanAndStdDeviationDistr{ 25, 40 };
	std::uniform_real_distribution<float> quantizationGammaForMainDistr{ 1.2, 2.5 };

	std::random_device rd{};
	std::mt19937 generator{ rd() };
	
	bool const normolizeImage{ true };
	for (size_t i{}; i < quantityImage; ++i)
	{
		int numberOfImageSize{ imageSizeDistr(generator) };
		cv::Size imageSize{ imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize] };
		
		size_t quantityCoefficient{ 2 };
		std::vector<float> correletionCoefficient(quantityCoefficient, 0.0);
		std::vector<float> sigmaForRandomCorrelationCoeficients(quantityCoefficient, 0.0);
		
		float correletionCoefficientValue{ correletionCoefficientDistr(generator) };
		for (auto& coefficient : correletionCoefficient)
			coefficient = correletionCoefficientDistr(generator);

		float sigmaForRandomCorrelationCoeficientsValue{ sigmaForRandomCorrelationCoeficientsDistr(generator) };
		for (auto& coefficient : sigmaForRandomCorrelationCoeficients)
			coefficient = sigmaForRandomCorrelationCoeficientsDistr(generator);
		

		float sigmaForRandomMean{ sigmaForRandomMeanDistr(generator) };
		float sigmaForRandomStdDeviation{ sigmaForRandomStdDeviationDistr(generator) };
		float meanForRandomMean{ meanForRandomMeanDistr(generator)};
		float meanForRandomStdDeviation{ meanForRandomStdDeviationDistr(generator)};
		float sigmaForMainImage{ sigmaForMainImageDistr(generator) };
		float quantizationGammaForCorrelationCoeficients{ quantizationGammaForCorrelationCoeficientsDistr(generator) };
		float quantizationGammaForMeanAndStdDeviation{ static_cast<float>(quantizationGammaForMeanAndStdDeviationDistr(generator)) };
		float quantizationGammaForMainImage{ quantizationGammaForMainDistr(generator)};
		
		SimpelTwiceRandomModel firstModel{ &imageSize, &correletionCoefficient };
		//cv::Mat twiceRandomImage{ firstModel.generateStandartMainImage() };
		cv::Mat twiceRandomImage{ firstModel.generateStandartMainImage(&sigmaForRandomCorrelationCoeficients,
															sigmaForRandomMean,
															sigmaForRandomStdDeviation,
															meanForRandomMean,
															meanForRandomStdDeviation,
															sigmaForMainImage,
															normolizeImage) };
		cv::normalize(twiceRandomImage, twiceRandomImage, 1.0, 0.0, cv::NORM_MINMAX);
		//std::vector<cv::Mat> simpelRandomImage{ firstModel.getRandomCorrelationCoefficients() };
		//for (auto& image : simpelRandomImage)
		//{
		//	cv::normalize(image, image, 1.0, 0.0, cv::NORM_MINMAX);
		//}
		
		HomogeneousArearsTwiceRandomModel secondModel{ &imageSize, &correletionCoefficient };
		//cv::Mat homogeneousArearsImage{ secondModel.generateStandartMainImage() };
		/*cv::Mat homogeneousArearsImage{ secondModel.generateStandartMainImage(&sigmaForRandomCorrelationCoeficients,
															sigmaForRandomMean,
															sigmaForRandomStdDeviation,
															meanForRandomMean,
															meanForRandomStdDeviation,
															sigmaForMainImage,
															quantizationGammaForCorrelationCoeficients,
															quantizationGammaForMeanAndStdDeviation,
															quantizationGammaForMainImage,
															normolizeImage) };*/
		//cv::normalize(homogeneousArearsImage, homogeneousArearsImage, 1.0, 0.0, cv::NORM_MINMAX);

		std::vector<cv::Mat> simpelHomogeneousArearsImage{ secondModel.getRandomCorrelationCoefficients() };
		
		for (auto& image : simpelHomogeneousArearsImage)
		{
			cv::normalize(image, image, 1.0, 0.0, cv::NORM_MINMAX);
		}
		
		
		//HeterogeneousTwiceRandomModel therdModel{ &imageSize, &correletionCoefficient };
		//cv::Mat heterogeneousTwiceRandomImage{ therdModel.generateStandartMainImage() };
		/*cv::Mat heterogeneousTwiceRandomImage{ therdModel.generateStandartMainImage(&sigmaForRandomCorrelationCoeficients,
															sigmaForRandomMean,
															sigmaForRandomStdDeviation,
															meanForRandomMean,
															meanForRandomStdDeviation,
															sigmaForMainImage,
															quantizationGammaForCorrelationCoeficients,
															quantizationGammaForMeanAndStdDeviation,
															quantizationGammaForMainImage,
															normolizeImage) };*/
		//cv::normalize(heterogeneousTwiceRandomImage, heterogeneousTwiceRandomImage, 1.0, 0.0, cv::NORM_MINMAX);
		//cv::imwrite("image/heterogeneousTwiceRandomImage.tiff", heterogeneousTwiceRandomImage);

		
		for (int i{ 0 }; i < twiceRandomImage.rows; ++i)
		{
			for (int j{ 0 }; j < twiceRandomImage.cols; ++j)
			{
				twiceRandomImage.at<float>(i, j) *= 255.0;
			}
		}

		size_t imageNumber{ startNumber + i };
		
		cv::imwrite("simpleTwiceRandomImageTest/twiceRandomImage_" + std::to_string(imageNumber) + ".png", twiceRandomImage);
		std::cout << imageNumber << std::endl;
	}
	return 0;
}