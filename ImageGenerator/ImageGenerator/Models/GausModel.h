#pragma once
#include "IImageModel.h"
#include "Parametrs/GausModelParametrs.h"

#include <random>

class GausModel :
    public IImageModel
{
    GausModelParametrs* param_{};
public:
    virtual void generateImage(cv::Mat& inOutImage);
    virtual void setParametrs(IModelParametrs* parametsr);
};

