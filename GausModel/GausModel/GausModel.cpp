#include <iostream>
#include <random>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
	size_t quantityImage{ 1 };
	size_t startNumber{ 0 };

	std::vector<int> imageWidth{ 640, 800, 960, 1024, 1280, 1280, 1600, 1920, 2048 };
	std::vector<int> imageHeigth{ 480, 600, 540, 600, 720, 1024, 900, 1080, 1080 };
	int quantityOfSize{ static_cast<int>(imageHeigth.size()) };
	std::uniform_int_distribution<> imageSizeDistr{ 0, quantityOfSize - 1 };
	std::uniform_int_distribution<> mediumDistr{ 50, 170 };
	std::uniform_int_distribution<> skoDistr{ 1, 10 };
	std::random_device rd{};
	std::mt19937 generator{ rd() };

	for (size_t i{}; i < quantityImage; ++i)
	{
		int numberOfImageSize{ imageSizeDistr(generator) };
        float medium{ static_cast<float>(mediumDistr(generator)) };
        float sko{ static_cast<float>(mediumDistr(generator)) };
        std::normal_distribution<float> dist(medium, sko);
		cv::Mat resultImage( imageHeigth[numberOfImageSize], imageWidth[numberOfImageSize], CV_8UC1 );
		for (int i{ 0 }; i < imageWidth[numberOfImageSize] * imageHeigth[numberOfImageSize]; ++i)
		{
			float val = dist(generator);
			if (val > 255.0)
			{
				val = 255.0;
			}
			else if (val < 0.0)
			{
				val = 0.0;
			}
			resultImage.data[i] = static_cast<unsigned char>(val);
		}

		size_t imageNumber{ startNumber + i };
		cv::imwrite("GausModel_test/GausModel_" + std::to_string(imageNumber) + ".png", resultImage);
		std::cout << imageNumber << std::endl;
	}
	return 0;
}