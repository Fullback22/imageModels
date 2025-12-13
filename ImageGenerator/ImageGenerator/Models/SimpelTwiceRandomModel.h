#pragma once
#include "IImageModel.h"
#include "Parametrs/SimpelTwiceRandomModelParametrs.h"

#include <random>
#include <vector>

class SimpelTwiceRandomModel :
    public IImageModel
{
    std::random_device rd_{};
    std::mt19937 generator_{ rd_() };
    cv::Mat mainImage_{};

    cv::Size imageSize{};
    
    std::vector<cv::Mat> randomCorrelationCoefficients{};
    cv::Mat randomMean{};
    cv::Mat randomStandatrDeviation{};

    SimpelTwiceRandomModelParametrs* param_{};

    
    void generateGausField(cv::Mat& gausFields, const double sigmaForRandomCoeficient);
    double getSigmaForGaus(double const sigmaForRandomCoeficients);

    cv::Mat generateSimpelRandomField(cv::Mat const gausRandomFields);
    void changeMeanInRandomFields(cv::Mat& inOutputImage, float const newMean);
    
    void generateRandomCorrelationCoefficients(const std::vector<double>& sigmaForCorrelationCoeficient);
    void generateRandomMean();
    void generateRandomStandatrDeviation();
    void changeMeanInRandomMean(float const newMean);
    void changeMeanInStandatrDeviation(float const newMean);

    cv::Mat normolizeImage(cv::Mat& inOutputImage);
    std::vector<cv::Mat> getRandomCorrelationCoefficients() const;
    cv::Mat generateMainImage();

public:
    void generateImage(cv::Mat& inOutImage) override;
    void setParametrs(IModelParametrs* parametrs) override;
    void computeParametrsForObject(IModelParametrs* parametrs, float contrast) override;
    int getMainObjectColor(float contrast) override;
};

