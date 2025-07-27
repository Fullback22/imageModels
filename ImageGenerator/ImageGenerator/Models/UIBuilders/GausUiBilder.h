#pragma once
#include "BaseModelParametrsUiBilder.h"
#include "../Parametrs/GausModelParametrs.h"

class GausUiBilder :
    public BaseModelParametrsUiBilder
{
    GausModelParametrs* modelParametrs_{};
	bool isInit_{ false };
	Q_OBJECT
	QLabel* label_medium{}, *label_sko{};
	QSpinBox* spBox_medium{}, *spBox_sko{};
	QHBoxLayout* horLayout_medium{}, * horLayout_sko{};
public:
	~GausUiBilder();
	void creatUi(QVBoxLayout& targetLayout) override;
	void toDefault() override;
	void clearForm() override;
	void setModel(IModelParametrs* modelParametrs) override;

protected slots:
	void slot_updateMedium(int newValue);
	void slot_updateSko(int newValue);
};


