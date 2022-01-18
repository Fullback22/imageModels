#include "WaveModel.h"

void WaveModel::generateWaveParams(float const propabilityThreshold, float const meanRadius, float const skoRadius, float const meanBrightness, float const skoBrightness)
{
	std::normal_distribution<float> Rdis{ meanRadius, skoRadius };
	std::normal_distribution<float> ksiDis{ meanBrightness, skoBrightness };
	std::poisson_distribution<int> puasonDistr{ static_cast<double>(densityPuasonDist * deltaT) };
		for (int i{ 0 }; i < mainImage.size().height; ++i)
		{
			for (int j{ 0 }; j < mainImage.size().width; ++j)
			{
				std::uniform_real_distribution<> dis{ 0.0, 1.0 };
				if (dis(gen) < propabilityThreshold)
				{
					waveCenter.push_back(cv::Point(j, i));
					R.push_back(Rdis(gen));
					ksi.push_back(ksiDis(gen));
				}
			}
		}
}

WaveModel::WaveModel(cv::Size const* imageSize, int const densityPuasonDist_):
	mainImage{ *imageSize, CV_8UC1, cv::Scalar(100) },
	densityPuasonDist{densityPuasonDist_},
	gen{rd()}
{
}

cv::Mat WaveModel::generateStandartMainImage()
{
	int const c{1};
	double const mu{ 0.1 };
	int const iteration{ 10 };

	for (int t{ 0 }; t < iteration; t += deltaT)
	{
		generateWaveParams(0.0001, 50, 15, 100, 30);
		cv::Mat lastImage{};
		mainImage.copyTo(lastImage);
		for (int i{ 0 }; i < mainImage.size().height; ++i)
		{
			for (int j{ 0 }; j < mainImage.size().width; ++j)
			{
				double secondSummand{ 0.0 };
				for (int z{ 0 }; z < waveCenter.size(); ++z)
				{
					double ro{ sqrt(pow(waveCenter[z].x - j, 2) + pow(waveCenter[z].y - i, 2)) };
					double toSqr{ ro / R[z] };
					double toExp{ pow(toSqr,2) * -2 };
					secondSummand += exp(toExp) * ksi[z];
				}
				double firstSummand{ std::exp(-mu * deltaT) };
				mainImage.at<uchar>(i, j) = lastImage.at<uchar>(i, j) * (firstSummand) + c * secondSummand;

			}

		}
		cv::imshow("image", mainImage);
		cv::waitKey(23);
	}
	return mainImage;
}

cv::Mat WaveModel::generateStandartMainImage(float const propabilityThreshold, 
											float const meanRadius,
											float const skoRadius,
											float const meanBrightness,
											float const skoBrightness,
											float const iteration,
											double const attenuation, 
											double const waveAmplification)
{
	for(int t{ 0 }; t < iteration; t += deltaT)
	{
		generateWaveParams(propabilityThreshold, meanRadius, skoRadius, meanBrightness, skoBrightness);
		cv::Mat lastImage{};
		mainImage.copyTo(lastImage);
		for (int i{ 0 }; i < mainImage.size().height; ++i)
		{
			for (int j{ 0 }; j < mainImage.size().width; ++j)
			{
				double secondSummand{ 0.0 };
				for (int z{ 0 }; z < waveCenter.size(); ++z)
				{
					double ro{ sqrt(pow(waveCenter[z].x - j, 2) + pow(waveCenter[z].y - i, 2)) };
					double toSqr{ ro / R[z] };
					double toExp{ pow(toSqr,2) * -2 };
					secondSummand += exp(toExp) * ksi[z];
				}
				double firstSummand{ std::exp(-attenuation * deltaT) };
				mainImage.at<uchar>(i, j) = lastImage.at<uchar>(i, j) * (firstSummand) + waveAmplification * secondSummand;
			}

		}
		cv::imshow("image", mainImage);
		cv::waitKey(23);
	}
	return mainImage;
}
