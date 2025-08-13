#pragma once
#include "IImageModel.h"
#include "Parametrs/GibsModelParametrs.h"

#include <random>

class GibsModel :
    public IImageModel
{
    std::random_device rd_{};
    std::mt19937 generator_{ rd_() };

    //unsigned int getNewValue(const std::vector<unsigned int>& frequncys);

    GibsModelParametrs* param_{};
public:
    void generateImage(cv::Mat& inOutImage) override;
    void setParametrs(IModelParametrs* parametrs) override;
    void computeParametrsForObject(IModelParametrs* parametrs, float contrast) override;
    int getMainObjectColor(float contrast) override;
};

