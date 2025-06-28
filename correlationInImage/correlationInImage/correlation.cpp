#include "correlation.h"

double medium(const int start, const int end)
{
    int sum{ 0 };
    for (int i{ start }; i < end; ++i)
        sum += i;

    return static_cast<double>(sum) / (end - start);
}

double squareOfDifference(const int start, const int end)
{
    double medium_{ medium(start, end) };
    double sum{};
    for (int i{ start }; i < end; ++i)
    {
        double delta{ i - medium_ };
        sum += pow(delta, 2.0);
    }
    return sum;
}

double correlationByCoordinate(const cv::Mat& image)
{
    double mediumImage{ medium<uchar>(image) };
    int end{ image.size().width };
    if (image.size().width == 1)
        end = image.size().height;
    double mediumCoordinate{ medium(0, end) };

    double squareOfDifferenceImage{ squareOfDifference<uchar>(image) };
    double squareOfDifferenceCoordinate{ squareOfDifference(0, end) };
    
    double sum{};
    if (image.size().height == 1)
    {
        for (int i{ }; i < end; ++i)
        {
            double deltaImage{ image.at<uchar>(0, i) - mediumImage };
            double deltaCoordinate{ i - mediumCoordinate };
            sum += deltaCoordinate * deltaImage;
        }
    }
    else if (image.size().width == 1)
    {
        for (int i{ }; i < end; ++i)
        {
            double deltaImage{ image.at<uchar>(i, 0) - mediumImage };
            double deltaCoordinate{ i - mediumCoordinate };
            sum += deltaCoordinate * deltaImage;
        }
    }
    if (sum == 0)
        return 0;
    return sum / sqrt(squareOfDifferenceImage * squareOfDifferenceCoordinate);
}

double correlationByNeighbor(const cv::Mat& image, const cv::Size& groupSize)
{
    cv::Mat medium_{};
    mediumNeighbor(image, medium_, groupSize);
    int dx{ (groupSize.width - 1) / 2 };
    int dy{ (groupSize.height - 1) / 2 };
    cv::Rect roi{ dx,dy,image.size().width - 2 * dx,image.size().height - 2 * dy };
    cv::Mat cutImage{ image(roi) };

    double mediumClass{ medium<uchar>(cutImage) };
    double mediumClassNeighbor{ medium<float>(medium_) };

    double sum{};
    for (size_t i{}; i < cutImage.size().height; ++i)
    {
        for (size_t j{}; j < cutImage.size().width; ++j)
        {
            double deltaClass{ cutImage.at<uchar>(i, j) - mediumClass };
            double deltaClassNeighbor{ medium_.at<float>(i, j) - mediumClassNeighbor };
            sum += deltaClass * deltaClassNeighbor;
        }
    }
    if (sum == 0)
        return 0;
    double squareOfDifferenceClass{ squareOfDifference<uchar>(cutImage) };
    double squareOfDifferenceClassNeighbor{ squareOfDifference<float>(medium_) };
    return sum / sqrt(squareOfDifferenceClass * squareOfDifferenceClassNeighbor);
}

void mediumNeighbor(const cv::Mat& input, cv::Mat& output, const cv::Size& filter)
{
    int delta_i{ filter.height - 1 };
    int delta_j{ filter.width - 1 };

    output.create(input.size().height - delta_i, input.size().width - delta_j, CV_32FC1);

    for (size_t image_i{}; image_i < output.size().height; ++image_i)
    {
        for (size_t image_j{}; image_j < output.size().width; ++image_j)
        {
            unsigned int sum{};
            for (size_t filter_i{}; filter_i < filter.height; ++filter_i)
            {
                for (size_t filter_j{}; filter_j < filter.width; ++filter_j)
                    sum += input.at<uchar>(image_i + filter_i, image_j + filter_j);
            }
            sum -= input.at<uchar>(image_i + filter.height / 2 + 1, image_j + filter.width / 2 + 1);
            output.at<float>(image_i, image_j) = static_cast<float>(sum) / (filter.area() - 1);
        }
    }

}
