#pragma once
#include "IModelParametrs.h"

#include <vector>
class MarkovModelParametrs :
    public IModelParametrs
{
public:
    unsigned int medium{};
    unsigned int step{};
    unsigned int quantityColors{};
    std::vector<std::vector<unsigned int>> conditionalTransitions;
};

