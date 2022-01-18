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
	cv::Size imageSize{ 600,400 };
	cv::Size blockSize{ 16,16 };

	
	cv::Mat mainImage{ imageSize, CV_8UC1 };
	std::vector<std::vector<int>> conditionalTransitions;
	int transitionsStep{ 10 };
	for (int i{ 0 }; i < 255; ++i)
	{
		conditionalTransitions.push_back(std::vector<int>(255,0));
		int transitionsFreqences{ 255 };
		for (int j{ i }; j < 255 && transitionsFreqences > 0; ++j)
		{
			conditionalTransitions[i][j] = transitionsFreqences;
			transitionsFreqences -= transitionsStep;
		}
		transitionsFreqences = 255;
		for (int j{ i }; j >= 0 && transitionsFreqences > 0; --j)
		{
			conditionalTransitions[i][j] = transitionsFreqences;
			transitionsFreqences -= transitionsStep;
		}
	}
	//MarkovFields markov(&imageSize);
	//markov.initConditionalTransitions(10);
	//markov.setConditionalTransitions(&conditionalTransitions);
	BlockMarkovModel blockMarkov{ &imageSize, &blockSize };
	cv::Mat test{ blockMarkov.generateStandartMainImage() };
	
	cv::imwrite("blockMarkovImage.png", test);
	cv::imshow("image", test);
	cv::waitKey();
	return 0;
}