#pragma once
#include "IModelParametrs.h"
#include <vector>

class SimpelTwiceRandomModelParametrs :
    public IModelParametrs
{
public:
    std::vector<double> correlationCoeficients{0.7, 0.7};
    std::vector<double> sifmaForCorrelationCoeficients{0.1, 0.1};
    float meanBrightness{};
    float skoBrightness{};
    float meanStdDeviation{};
    float skoStdDeviation{};
    float skoForMainImage{};
};

