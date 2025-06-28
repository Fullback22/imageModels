#include <random>
#include <iostream>
#include <numeric>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "GibsModel.h"
#include "BlockGibsModel.h"

int main()
{
	size_t quantityImage{ 180 };
	size_t startNumber{ 360 };
	
	int quantityClasses{ 5 };
	std::vector<int> startFrenqce{ 1,1,1,1,1 };
	std::vector<std::vector<int>> propabilityMap(quantityClasses);

	propabilityMap[0] = std::vector<int>{ 1,1,1,1,1 };
	propabilityMap[1] = std::vector<int>{ 1,1,1,1,1 };
	propabilityMap[2] = std::vector<int>{ 1,1,1,1,1 };
	propabilityMap[3] = std::vector<int>{ 1,1,1,1,1 };
	propabilityMap[4] = std::vector<int>{ 1,1,1,1,1 };
	
	std::uniform_int_distribution<> blockSizeDistr{ 4, 12 };
	std::vector<int> imageWidth{ 640, 800, 960, 1024, 1280, 1280, 1600, 1920, 2048 };
	std::vector<int> imageHeigth{ 480, 600, 540, 600, 720, 1024, 900, 1080, 1080 };
	int quantityOfSize{ static_cast<int>(imageHeigth.size()) };
	std::uniform_int_distribution<> imageSizeDistr{ 0, quantityOfSize - 1 };
	std::random_device rd_{};
	std::mt19937 generator{ rd_() };
	
	//for (size_t i{}; i < quantityImage; ++i)
	//{
	//	
	//	int numberOfImageSize{ imageSizeDistr(generator) };
	//	//GibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]} };
	//	cv::Size blockSize{ blockSizeDistr(generator), blockSizeDistr(generator) };
	//	BlockGibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]}, blockSize };
	//	
	//	cv::Mat resultImage{ gibsImage.generateStandartMainImage(startFrenqce, propabilityMap, 100, false) };

	//	int step{ 20 };
	//	for (int i{ 0 }; i < imageHeigth[numberOfImageSize]; ++i)
	//	{
	//		for (int j{ 0 }; j < imageWidth[numberOfImageSize]; ++j)
	//		{
	//			resultImage.at<uchar>(i, j) = resultImage.at<uchar>(i, j) * step;
	//		}
	//	}
	//	size_t imageNumber{ startNumber + i };
	//	cv::imwrite("blockGibsModel/blockGibsModel_" + std::to_string(imageNumber)+ ".png", resultImage);
	//	std::cout << imageNumber << std::endl;
	//}
	//
	//startNumber += quantityImage;
	//propabilityMap[0] = std::vector<int>{ 3,1,1,1,1 };
	//propabilityMap[1] = std::vector<int>{ 1,3,1,1,1 };
	//propabilityMap[2] = std::vector<int>{ 1,1,3,1,1 };
	//propabilityMap[3] = std::vector<int>{ 1,1,1,3,1 };
	//propabilityMap[4] = std::vector<int>{ 1,1,1,1,3 };

	//for (size_t i{}; i < quantityImage; ++i)
	//{

	//	int numberOfImageSize{ imageSizeDistr(generator) };
	//	//GibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]} };
	//	cv::Size blockSize{ blockSizeDistr(generator), blockSizeDistr(generator) };
	//	BlockGibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]}, blockSize };

	//	cv::Mat resultImage{ gibsImage.generateStandartMainImage(startFrenqce, propabilityMap, 100, false) };

	//	int step{ 20 };
	//	for (int i{ 0 }; i < imageHeigth[numberOfImageSize]; ++i)
	//	{
	//		for (int j{ 0 }; j < imageWidth[numberOfImageSize]; ++j)
	//		{
	//			resultImage.at<uchar>(i, j) = resultImage.at<uchar>(i, j) * step;
	//		}
	//	}
	//	size_t imageNumber{ startNumber + i };
	//	cv::imwrite("blockGibsModel/blockGibsModel_" + std::to_string(imageNumber) + ".png", resultImage);
	//	std::cout << imageNumber << std::endl;
	//}
	//startNumber += quantityImage;
	quantityClasses = 4;
	startFrenqce = std::vector<int>{ 1,1,1,1 };
	propabilityMap = std::vector<std::vector<int>>(quantityClasses);

	propabilityMap[0] = std::vector<int>{ 1,1,1,1 };
	propabilityMap[1] = std::vector<int>{ 1,1,1,1 };
	propabilityMap[2] = std::vector<int>{ 1,1,1,1 };
	propabilityMap[3] = std::vector<int>{ 1,1,1,1 };

	for (size_t i{}; i < quantityImage; ++i)
	{
		int numberOfImageSize{ imageSizeDistr(generator) };
		//GibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]} };
		cv::Size blockSize{ blockSizeDistr(generator), blockSizeDistr(generator) };
		BlockGibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]}, blockSize };

		cv::Mat resultImage{ gibsImage.generateStandartMainImage(startFrenqce, propabilityMap, 100, false) };

		int step{ 20 };
		for (int i{ 0 }; i < imageHeigth[numberOfImageSize]; ++i)
		{
			for (int j{ 0 }; j < imageWidth[numberOfImageSize]; ++j)
			{
				resultImage.at<uchar>(i, j) = resultImage.at<uchar>(i, j) * step;
			}
		}
		size_t imageNumber{ startNumber + i };
		cv::imwrite("blockGibsModel/blockGibsModel_" + std::to_string(imageNumber) + ".png", resultImage);
		std::cout << imageNumber << std::endl;
	}
	startNumber += quantityImage;
	propabilityMap[0] = std::vector<int>{ 3,1,1,1 };
	propabilityMap[1] = std::vector<int>{ 1,3,1,1 };
	propabilityMap[2] = std::vector<int>{ 1,1,3,1 };
	propabilityMap[3] = std::vector<int>{ 1,1,1,3 };

	//for (size_t i{}; i < quantityImage; ++i)
	//{

	//	int numberOfImageSize{ imageSizeDistr(generator) };
	//	//GibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]} };
	//	cv::Size blockSize{ blockSizeDistr(generator), blockSizeDistr(generator) };
	//	BlockGibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]}, blockSize };

	//	cv::Mat resultImage{ gibsImage.generateStandartMainImage(startFrenqce, propabilityMap, 100, false) };

	//	int step{ 20 };
	//	for (int i{ 0 }; i < imageHeigth[numberOfImageSize]; ++i)
	//	{
	//		for (int j{ 0 }; j < imageWidth[numberOfImageSize]; ++j)
	//		{
	//			resultImage.at<uchar>(i, j) = resultImage.at<uchar>(i, j) * step;
	//		}
	//	}
	//	size_t imageNumber{ startNumber + i };
	//	cv::imwrite("blockGibsModel/blockGibsModel_" + std::to_string(imageNumber) + ".png", resultImage);
	//	std::cout << imageNumber << std::endl;
	//}

	//startNumber += quantityImage;
	//quantityClasses = 3;
	//startFrenqce = std::vector<int>{ 1,1,1 };
	//propabilityMap = std::vector<std::vector<int>>(quantityClasses);

	//propabilityMap[0] = std::vector<int>{ 1,1,1 };
	//propabilityMap[1] = std::vector<int>{ 1,1,1 };
	//propabilityMap[2] = std::vector<int>{ 1,1,1 };

	//for (size_t i{}; i < quantityImage; ++i)
	//{
	//	int numberOfImageSize{ imageSizeDistr(generator) };
	//	//GibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]} };
	//	cv::Size blockSize{ blockSizeDistr(generator), blockSizeDistr(generator) };
	//	BlockGibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]}, blockSize };

	//	cv::Mat resultImage{ gibsImage.generateStandartMainImage(startFrenqce, propabilityMap, 100, false) };

	//	int step{ 20 };
	//	for (int i{ 0 }; i < imageHeigth[numberOfImageSize]; ++i)
	//	{
	//		for (int j{ 0 }; j < imageWidth[numberOfImageSize]; ++j)
	//		{
	//			resultImage.at<uchar>(i, j) = resultImage.at<uchar>(i, j) * step;
	//		}
	//	}
	//	size_t imageNumber{ startNumber + i };
	//	cv::imwrite("blockGibsModel/blockGibsModel_" + std::to_string(imageNumber) + ".png", resultImage);
	//	std::cout << imageNumber << std::endl;
	//}
	//startNumber += quantityImage;
	//propabilityMap[0] = std::vector<int>{ 3,1,1 };
	//propabilityMap[1] = std::vector<int>{ 1,3,1 };
	//propabilityMap[2] = std::vector<int>{ 1,1,3 };

	//for (size_t i{}; i < quantityImage; ++i)
	//{

	//	int numberOfImageSize{ imageSizeDistr(generator) };
	//	//GibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]} };
	//	cv::Size blockSize{ blockSizeDistr(generator), blockSizeDistr(generator) };
	//	BlockGibsModel gibsImage{ cv::Size{imageWidth[numberOfImageSize], imageHeigth[numberOfImageSize]}, blockSize };

	//	cv::Mat resultImage{ gibsImage.generateStandartMainImage(startFrenqce, propabilityMap, 100, false) };

	//	int step{ 20 };
	//	for (int i{ 0 }; i < imageHeigth[numberOfImageSize]; ++i)
	//	{
	//		for (int j{ 0 }; j < imageWidth[numberOfImageSize]; ++j)
	//		{
	//			resultImage.at<uchar>(i, j) = resultImage.at<uchar>(i, j) * step;
	//		}
	//	}
	//	size_t imageNumber{ startNumber + i };
	//	cv::imwrite("blockGibsModel/blockGibsModel_" + std::to_string(imageNumber) + ".png", resultImage);
	//	std::cout << imageNumber << std::endl;
	//}
}