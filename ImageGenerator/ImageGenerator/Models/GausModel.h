#pragma once
#include "IImageModel.h"
#include "Parametrs/GausModelParametrs.h"

#include <random>

class GausModel :
    public IImageModel
{
    GausModelParametrs* param_{};
public:
    void generateImage(cv::Mat& inOutImage) override;
    void setParametrs(IModelParametrs* parametsr) override;
    void computeParametrsForObject(IModelParametrs* parametrs, float contrast) override;
    int getMainObjectColor(float contrast) override;
};

