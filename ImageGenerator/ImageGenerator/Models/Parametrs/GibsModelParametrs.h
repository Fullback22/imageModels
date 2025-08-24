#pragma once
#include "IModelParametrs.h"
#include <vector>

class GibsModelParametrs :
    public IModelParametrs
{
public:
    unsigned int medium{};
    unsigned int step{};
    unsigned int quantityColors{};
    unsigned int quaantityIteration{};
    std::vector<std::vector<unsigned int>> propabilityMap;
    std::vector<int> startFrequencyClasses;
};

