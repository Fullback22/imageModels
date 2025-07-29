#pragma once
#include "IModelParametrsUiBilder.h"
#include "qspinbox.h"
#include "qlabel.h"

class BaseModelParametrsUiBilder :
    public IModelParametrsUiBilder
{
	Q_OBJECT
	
	bool isInit_{ false };

protected:
	IModelParametrs* modelParametrs_{};
	QLabel* label_width{}, * label_heigth{};
	QSpinBox* spBox_width{}, * spBox_heigth{};
	QHBoxLayout* horLayout_width{}, * horLayout_heigth{};
public:
	void creatUi(QVBoxLayout& targetLayout) override;
	void toDefault() override;
	void clearForm() override;
	void setModel(IModelParametrs* modelParametrs)override;
	bool parametrsIsCorrect() const override { return true; };

protected slots:
	void slot_updateWidth(int newValue);
	void slot_updateHeigth(int newValue);
};

