#pragma once
#include "IModelParametrs.h"

#include <vector>
class MarkovModelParametrs :
    public IModelParametrs
{
public:
    int medium{};
    int step{};
    int quantityColors{};
    std::vector<std::vector<int>> conditionalTransitions;
};

