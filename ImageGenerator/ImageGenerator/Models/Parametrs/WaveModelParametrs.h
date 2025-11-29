#pragma once
#include "IModelParametrs.h"
class WaveModelParametrs :
    public IModelParametrs
{
public:
    float meanBrightness{};
    float skoBrightness{};
    unsigned int distThreshold{};
    float meanRadius{};
    float skoRadius{};
};

