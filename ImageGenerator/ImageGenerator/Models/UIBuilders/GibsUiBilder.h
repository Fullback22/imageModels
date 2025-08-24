#pragma once
#include <qscrollarea.h>
#include <qgridlayout.h>

#include "BaseModelParametrsUiBilder.h"
#include "../Parametrs/GibsModelParametrs.h"
#include "ProbabilitiesFieldWidget.h"

class GibsUiBilder:
	public BaseModelParametrsUiBilder
{
	GibsModelParametrs* modelParametrs_{};
	bool isInit_{ false };
	bool fieldIsResize{ false };
	Q_OBJECT
	QLabel* label_medium{}, * label_step{}, * label_quantityIteration{},* label_quantityColors{}, * label_probabilities{}, * label_startFrequencies{};
	QSpinBox* spBox_medium{}, * spBox_step{}, * spBox_quantityColors{}, * spBox_quantityIteration{};
	QHBoxLayout* horLayout_medium{}, * horLayout_step{}, * horLayout_quantityColors{}, * horLayout_quantityIteration{};
	ProbabilitiesFieldWidget* field{}, *startFrequenciesField{};

public:
	~GibsUiBilder();
	void creatUi(QVBoxLayout& targetLayout) override;
	void toDefault() override;
	void clearForm() override;
	void setModel(IModelParametrs* modelParametrs) override;
	bool parametrsIsCorrect()const override;

protected slots:
	void slot_updateMedium(int newValue);
	void slot_updateStep(int newValue);
	void slot_updateQuantityColors(int newValue);
	void slot_updateQuantityItterations(int newValue);
	void slot_updateProbobilityMap();
};

