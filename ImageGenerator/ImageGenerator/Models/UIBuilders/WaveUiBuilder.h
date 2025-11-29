#pragma once
#include "BaseModelParametrsUiBilder.h"
#include "../Parametrs/WaveModelParametrs.h"


class WaveUiBuilder :
    public BaseModelParametrsUiBilder
{
	WaveModelParametrs* modelParametrs_{};
	bool isInit_{ false };

	Q_OBJECT
	QLabel* label_mediumBrignest{}, * label_skoBrignest{}, * label_mediumRadius{}, * label_skoRadiusm{}, * label_threshold{};
	QSpinBox* spBox_mediumBrignest{}, * spBox_skoBrignest{}, *spBox_mediumRadius{}, * spBox_skoRadius{}, * spBox_threshold{};
	QHBoxLayout* horLayout_mediumBrignest{}, * horLayout_skoBrignest{}, *horLayout_mediumRadius{}, * horLayout_skoRadius{}, * horLayout_threshold{};

public:
	~WaveUiBuilder();
	void creatUi(QVBoxLayout& targetLayout) override;
	void toDefault() override;
	void clearForm() override;
	void setModel(IModelParametrs* modelParametrs) override;
	bool parametrsIsCorrect()const override;

protected slots:
	void slot_updateMediumBrignest(int newValue);
	void slot_updateSkoBrignest(int newValue);
	void slot_updateMediumRadius(int newValue);
	void slot_updateSkoRadius(int newValue);
	void slot_updateThreshold(int newValue);
};

