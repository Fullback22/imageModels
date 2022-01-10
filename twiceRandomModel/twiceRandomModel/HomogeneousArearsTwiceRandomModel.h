#pragma once
#include "SimpelTwiceRandomModel.h"

class HomogeneousArearsTwiceRandomModel :
    public SimpelTwiceRandomModel
{
    float quantization(float const value, float const gama);
    cv::Mat generateSimpelRandomField(cv::Mat const gausRandomFields, float const gama);
public:
    HomogeneousArearsTwiceRandomModel(cv::Size* const imageSize, std::vector<float>* correlationCoefficients);
    void generateRandomCorrelationCoefficients(float const gama);
    void generateRandomMean(float const gama);
    void generateRandomStandatrDeviation(float const gama);
    cv::Mat generateMainImage(float const gama);
    cv::Mat generateStandartMainImage();
    cv::Mat generateStandartMainImage(std::vector<float>* const sigmaForRandomCorrelationCoeficients,
        float const sigmaForRandomMean,
        float const sigmaForRandomStdDeviation,
        float const meanForRandomMean,
        float const meanForRandomStdDeviation,
        float const sigmaForMainImage,
        float const quantizationGammaForCorrelationCoeficients,
        float const quantizationGammaForMeanAndStdDeviation,
        float const quantizationGammaForMainImage,
        bool const normolizeImage = true);
};

