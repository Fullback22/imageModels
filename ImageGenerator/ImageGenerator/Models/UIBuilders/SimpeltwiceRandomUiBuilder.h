#pragma once
#include "BaseModelParametrsUiBilder.h"
#include "../Parametrs/SimpelTwiceRandomModelParametrs.h"
#include "UiDoubleModelParametr.h"

class SimpeltwiceRandomUiBuilder :
    public BaseModelParametrsUiBilder
{
	SimpelTwiceRandomModelParametrs* modelParametrs_{};
	bool isInit_{ false };
	Q_OBJECT

	QVector<UiDoubleModelParametr*> parametrs{9, nullptr};
public:
	~SimpeltwiceRandomUiBuilder();
	void creatUi(QVBoxLayout& targetLayout) override;
	void toDefault() override;
	void clearForm() override;
	void setModel(IModelParametrs* modelParametrs) override;
	bool parametrsIsCorrect()const override { return true; };

protected slots:
	void slot_firstCorrelationCoeficients(double newValue);
	void slot_secondCorrelationCoeficients(double newValue);
	void slot_firstSigmaCorrelationCoeficients(double newValue);
	void slot_secondSigmaCorrelationCoeficients(double newValue);
	void slot_meanBrightness(double newValue);
	void slot_skoBrightness(double newValue);
	void slot_meanStdDeviation(double newValue);
	void slot_skoStdDeviation(double newValue);
	void slot_skoForMainImage(double newValue);
};

