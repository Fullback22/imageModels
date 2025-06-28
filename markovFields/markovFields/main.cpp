#include <iostream>
#include <random>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include"MarkovFields.h"
#include"BlockMarkovModel.h"

int main()
{
	size_t quantityImage{ 5 };
	size_t startNumber{ 159 };

	
	int quantityClasses{ 3 };
	std::vector<std::vector<int>> conditionalTransitions(quantityClasses);
	
	conditionalTransitions[0] = std::vector<int>{ 3,2,1 };
	conditionalTransitions[1] = std::vector<int>{ 3,2,1 };
	conditionalTransitions[2] = std::vector<int>{ 3,2,1 };
	//conditionalTransitions[3] = std::vector<int>{ 1,2,3,4 };
	//conditionalTransitions[4] = std::vector<int>{ 1,2,4,5,5 };

	std::uniform_int_distribution<> blockSizeDistr{ 4, 12 };
	std::vector<int> imageWidth{ 640, 800, 960, 1024, 1280, 1280, 1600, 1920, 2048 };
	std::vector<int> imageHeigth{ 480, 600, 540, 600, 720, 1024, 900, 1080, 1080 };
	int quantityOfSize{ static_cast<int>(imageHeigth.size()) };
	std::uniform_int_distribution<> imageSizeDistr{ 0, quantityOfSize - 1 };
	std::random_device rd_{};
	std::mt19937 generator{ rd_() };
	for (size_t i{}; i < quantityImage; ++i)
	{
		int numberOfImageSize{ imageSizeDistr(generator) };
		
		cv::Size blockSize{ blockSizeDistr(generator), blockSizeDistr(generator) };
		//MarkovFields markov{ cv::Size{ imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize] } };
		//markov.setConditionalTransitions(conditionalTransitions);
		BlockMarkovModel blockMarkov{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]}, blockSize };
		cv::Mat resultImage{ blockMarkov.generateStandartMainImage(conditionalTransitions) };
		
		int step{ 20 };
		for (int i{ 0 }; i < imageHeigth[numberOfImageSize]; ++i)
		{
			for (int j{ 0 }; j < imageWidth[numberOfImageSize]; ++j)
			{
				resultImage.at<uchar>(i, j) = resultImage.at<uchar>(i, j) * step;
			}
		}

		size_t imageNumber{ startNumber + i };
		cv::imwrite("blockMarkovModel/blockMarkovModel_" + std::to_string(imageNumber) + ".png", resultImage);
		std::cout << imageNumber << std::endl;
	}
	return 0;
}