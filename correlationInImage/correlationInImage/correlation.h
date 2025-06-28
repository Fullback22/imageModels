#pragma once
#include <opencv2/core/core.hpp>

template <typename T>
double medium(const cv::Mat& image)
{
    int sum{};
    for (size_t i{}; i < image.size().height; ++i)
    {
        for (size_t j{}; j < image.size().width; ++j)
            sum += image.at<T>(i, j);
    }

    return static_cast<double>(sum) / image.size().area();
};

double medium(const int start, const int end);

template <typename T>
double squareOfDifference(const cv::Mat& image)
{
    double medium_{ medium<T>(image) };
    double sum{};
    for (size_t i{}; i < image.size().height; ++i)
    {
        for (size_t j{}; j < image.size().width; ++j)
        {
            double delta{ image.at<T>(i, j) - medium_ };
            sum += pow(delta, 2.0);
        }
    }
    return sum;
};

double squareOfDifference(const int start, const int end);

double correlationByCoordinate(const cv::Mat& image);

double correlationByNeighbor(const cv::Mat& image, const cv::Size& groupSize);

void mediumNeighbor(const cv::Mat& input, cv::Mat& output, const cv::Size& area);
