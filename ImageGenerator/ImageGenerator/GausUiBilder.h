#pragma once
#include "qspinbox.h"
#include "qlabel.h"

#include "BaseModelParametrsUiBilder.h"
#include "Models/Parametrs/GausModelParametrs.h"

class GausUiBilder :
    public BaseModelParametrsUiBilder
{
    GausModelParametrs* modelParametrs{};
	Q_OBJECT
	QLabel* label_medium{}, * label_sko{};
	QSpinBox* spBox_medium{}, * spBox_sko{};
	QHBoxLayout* horLayout_medium{}, * horLayout_sko{};
public:
	~GausUiBilder();
	void creatUi(QVBoxLayout& targetLayout) override;
	void toDefault() override {};
	void clear() override {};
	void setModel(const IModelParametrs* modelParametrs) {};
};

