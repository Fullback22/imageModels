#pragma once
#include <qscrollarea.h>
#include <qgridlayout.h>

#include "BaseModelParametrsUiBilder.h"
#include "../Parametrs/MarkovModelParametrs.h"
#include "ProbabilitiesFieldWidget.h"

class MarkovUiBilder :
    public BaseModelParametrsUiBilder
{
	MarkovModelParametrs* modelParametrs_{};
	bool isInit_{ false };
	Q_OBJECT
	QLabel* label_medium{}, * label_step{}, * label_quantityColors{}, * label_probabilities{};
	QSpinBox* spBox_medium{}, * spBox_step{}, *spBox_quantityColors{};
	QHBoxLayout* horLayout_medium{}, * horLayout_step{}, *horLayout_quantityColors{};
	ProbabilitiesFieldWidget* field{};
public:
	~MarkovUiBilder();
	void creatUi(QVBoxLayout& targetLayout) override;
	void toDefault() override;
	void clearForm() override;
	void setModel(IModelParametrs* modelParametrs) override;

protected slots:
	void slot_updateMedium(int newValue);
	void slot_updateStep(int newValue);
	void slot_updateQuantityColors(int newValue);
};

