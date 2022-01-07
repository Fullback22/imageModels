#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "iostream"
#include <random>

float sigmaForGaus(float const r, float const sigmaRo)
{
	float rSqear{ r * r };
	float deviatio{ (1 - rSqear) * (1 - rSqear) * sigmaRo * sigmaRo };
	return std::sqrt(deviatio);
}

float getRandom(bool pozitiv = true)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::normal_distribution<float> dist(0, 0.0361);
	for (;;)
	{
		float random{ dist(gen) };
		if (pozitiv && random > 0)
			return random;
		else if (!pozitiv && random < 0)
			return random;
	}
}

void gausInit(std::vector<cv::Mat>& inputOutputGaus, cv::Size const imageSize, int const quantytiImage = 2, float const SKO = 1, float const medium = 0.0)
{
	for (int z{ 0 }; z < quantytiImage; ++z)
	{
		cv::Mat buferImage{ imageSize, CV_32FC1 };
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::normal_distribution<float> dist(medium, SKO);
		for (int i{ 0 }; i < imageSize.height; ++i)
		{
			for (int j{ 0 }; j < imageSize.width; ++j)
			{
				buferImage.at<float>(i, j) = dist(gen);
			}
		}
		inputOutputGaus.push_back(buferImage);
	}
}

void genRo(std::vector<cv::Mat> &inputOutputRo, std::vector<cv::Mat> const* inputGaus, std::vector<float> const* r)
{
	for (int z{ 0 }; z < inputGaus->size(); ++z)
	{
		cv::Mat buferImage{ (*inputGaus)[0].size(), CV_32FC1 };

		buferImage.at<float>(0, 0) = (*inputGaus)[z].at<float>(0, 0);
		for (int i{ 1 }; i < buferImage.size().width; ++i)
		{
			buferImage.at<float>(0, i) = (*r)[z] * buferImage.at<float>(0, i - 1) + (*inputGaus)[z].at<float>(0, i);
		}
		for (int i{ 1 }; i < buferImage.size().height; ++i)
		{
			buferImage.at<float>(i, 0) = (*r)[z] * buferImage.at<float>(i - 1, 0) + (*inputGaus)[z].at<float>(i, 0);
		}
		for (int i{ 1 }; i < buferImage.size().height; ++i)
		{
			for (int j{ 1 }; j < buferImage.size().width; ++j)
			{
				float rx{ (*r)[z] * buferImage.at<float>(i, j - 1) };
				float ry{ (*r)[z] * buferImage.at<float>(i - 1, j) };
				float rxy{ (*r)[z] * (*r)[z] * buferImage.at<float>(i - 1, j - 1) };

				buferImage.at<float>(i, j) = rx + ry - rxy + (*inputGaus)[z].at<float>(i, j);
			}
		}
		inputOutputRo.push_back(buferImage);
	}
}

cv::Mat generateImage(std::vector<cv::Mat> const* inputRo, std::vector<cv::Mat> const* inputAb, cv::Mat const* inputGaus)
{
	cv::Mat buferImage{ (*inputRo)[0].size(), CV_32FC1 };
	
	buferImage.at<float>(0, 0) = (*inputAb)[0].at<float>(0, 0) + (*inputAb)[1].at<float>(0, 0) * (*inputGaus).at<float>(0, 0);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		float rx{ (*inputRo)[0].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		float rxy{ (*inputRo)[0].at<float>(0, i) * (*inputRo)[1].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		buferImage.at<float>(0, i) = (*inputAb)[0].at<float>(0, i) + rx - rxy + (*inputAb)[1].at<float>(0, i) * (*inputGaus).at<float>(0, i);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		float ry{ (*inputRo)[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		float rxy{ (*inputRo)[0].at<float>(i, 0) * (*inputRo)[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		buferImage.at<float>(i, 0) = (*inputAb)[0].at<float>(i, 0) + ry - rxy + (*inputAb)[1].at<float>(i, 0) * (*inputGaus).at<float>(i, 0);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			float rx{ (*inputRo)[0].at<float>(i, j) * buferImage.at<float>(i, j - 1) };
			float ry{ (*inputRo)[1].at<float>(i, j) * buferImage.at<float>(i - 1, j) };
			float rxy{ (*inputRo)[0].at<float>(i, j) * (*inputRo)[1].at<float>(i, j) * buferImage.at<float>(i - 1, j - 1) };

			buferImage.at<float>(i, j) = (*inputAb)[0].at<float>(i, j) + rx + ry - rxy + (*inputAb)[1].at<float>(i, j) * (*inputGaus).at<float>(i, j);
		}
	}
	
	return buferImage;
}

cv::Mat generateImageTest(std::vector<cv::Mat> const* inputRo, std::vector<cv::Mat> const* inputAb, cv::Mat const* inputGaus)
{
	cv::Mat buferImage{ (*inputRo)[0].size(), CV_32FC1 };

	buferImage.at<float>(0, 0) = (*inputAb)[0].at<float>(0, 0) + (*inputAb)[1].at<float>(0, 0) * (*inputGaus).at<float>(0, 0);
	for (int i{ 1 }; i < buferImage.size().width; ++i)
	{
		float rx{ (*inputRo)[0].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		float rxy{ (*inputRo)[0].at<float>(0, i) * (*inputRo)[1].at<float>(0, i) * buferImage.at<float>(0, i - 1) };
		buferImage.at<float>(0, i) = (*inputAb)[0].at<float>(0, i) + rx - rxy + (*inputAb)[1].at<float>(0, i) * (*inputGaus).at<float>(0, i);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		float ry{ (*inputRo)[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		float rxy{ (*inputRo)[0].at<float>(i, 0) * (*inputRo)[1].at<float>(i, 0) * buferImage.at<float>(i - 1, 0) };
		buferImage.at<float>(i, 0) = (*inputAb)[0].at<float>(i, 0) + ry - rxy + (*inputAb)[1].at<float>(i, 0) * (*inputGaus).at<float>(i, 0);
	}
	for (int i{ 1 }; i < buferImage.size().height; ++i)
	{
		for (int j{ 1 }; j < buferImage.size().width; ++j)
		{
			float rx{ (*inputRo)[0].at<float>(i, j) * buferImage.at<float>(i, j - 1) };
			float ry{ (*inputRo)[1].at<float>(i, j) * buferImage.at<float>(i - 1, j) };
			float rxy{ (*inputRo)[0].at<float>(i, j) * (*inputRo)[1].at<float>(i, j) * buferImage.at<float>(i - 1, j - 1) };

			buferImage.at<float>(i, j) = (*inputAb)[0].at<float>(i, j) + rx + ry - rxy + (*inputAb)[1].at<float>(i, j) * (*inputGaus).at<float>(i, j);
		}
	}

	return buferImage;
}

void changeMo(cv::Mat& inOutputImage, float const newMo)
{
	for (int i{ 0 }; i < inOutputImage.size().height; ++i)
	{
		for (int j{ 0 }; j < inOutputImage.size().width; ++j)
		{
			inOutputImage.at<float>(i, j) = inOutputImage.at<float>(i, j) + newMo;
		}
	}
	return;
}
int main()
{
	std::vector<float> r(2, 0.99);

	cv::Size imageSize{ 600, 400 };
	std::vector<cv::Mat> gaus{};
	std::vector<cv::Mat> ro{};
	std::vector<cv::Mat> ab{};
	float sko{ sigmaForGaus(r[0], 0.2) };
	gausInit(gaus, imageSize, 2, sko, 0);

	genRo(ro, &gaus, &r);
	genRo(ab, &gaus, &r);

	cv::Mat stdM{};
	cv::Mat meanM{};
	cv::meanStdDev(ro[0], meanM, stdM);
	cv::meanStdDev(ro[0], meanM, stdM);
	
	gaus.clear();
	gausInit(gaus, imageSize, 1, sko);

	cv::Mat qwe{ generateImage(&ro, &ab, &gaus[0]) };
	changeMo(ab[0], 0.99);
	changeMo(ab[1], 0.99);
	cv::Mat qwe1{ generateImage(&ro, &ab, &gaus[0]) };
	//cv::Mat qwe{ generateImage2(&ro, &gaus[0]) };
	cv::normalize(qwe, qwe, 1.0, 0.0, cv::NORM_MINMAX);
	cv::normalize(qwe1, qwe1, 1.0, 0.0, cv::NORM_MINMAX);
	cv::normalize(ro[0], ro[0], 1.0, 0.0, cv::NORM_MINMAX);
	cv::normalize(ro[1], ro[1], 1.0, 0.0, cv::NORM_MINMAX);
	
	cv::imshow("histogram", ro[0]);
	cv::imshow("background", ro[1]);
	cv::imshow("image", qwe);
	cv::imshow("image1", qwe1);
	cv::waitKey();
	return 0;
}