#pragma once
#include "IModelParametrsUiBilder.h"
class BaseModelParametrsUiBilder :
    public IModelParametrsUiBilder
{

public:
	void creatUi(QVBoxLayout& targetLayout) override{};
	void toDefault() override{};
	void clear() override{};
	void setModel(const IModelParametrs* modelParametrs) {};
};

