#pragma once
#include "IImageModel.h"
#include "Parametrs/WaveModelParametrs.h"

#include <random>
#include <vector>

class WaveModel :
    public IImageModel
{
    struct WaveParams
    {
        cv::Point center{};
        float R{};
        float ksi{};
    };
    size_t const iteration{ 3 };
    WaveModelParametrs* param_{};
    std::vector<WaveParams> waveParams_{};
    cv::Mat mainImage_{};

    void generateWaveParams();
public:
    void generateImage(cv::Mat& inOutImage) override;
    void setParametrs(IModelParametrs* parametrs) override;
    void computeParametrsForObject(IModelParametrs* parametrs, float contrast) override;
    int getMainObjectColor(float contrast) override;

};

