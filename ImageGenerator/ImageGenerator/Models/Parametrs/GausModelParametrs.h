#pragma once
#include "IModelParametrs.h"
class GausModelParametrs :
    public IModelParametrs
{
public:
    float medium{};
    float sko{};
};

