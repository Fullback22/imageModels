#pragma once
#include "IModelParametrs.h"

class SimpelTwiceRandomModelParametrs :
    public IModelParametrs
{
public:

    float meanRandomMean{};
    float skoRandomMean{};
    float meanRandomStdDeviation{};
    float skoRandomStdDeviation{};
    float sko{};
};

