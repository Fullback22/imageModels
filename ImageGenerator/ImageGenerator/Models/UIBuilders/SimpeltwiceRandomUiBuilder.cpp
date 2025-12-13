#include "SimpeltwiceRandomUiBuilder.h"

SimpeltwiceRandomUiBuilder::~SimpeltwiceRandomUiBuilder()
{
	clearForm();
}

void SimpeltwiceRandomUiBuilder::creatUi(QVBoxLayout& targetLayout)
{
	BaseModelParametrsUiBilder::creatUi(targetLayout);
	parametrs[0] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("Первый коэффициент корреляции"), 1.0);
	parametrs[1] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("Второй коэффициент корреляции"), 1.0);
	parametrs[2] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("Сигма певого коэффициента корреляции"), 1.0);
	parametrs[3] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("Сигма второго коэффициента корреляции"), 1.0);
	parametrs[4] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("Средняя яркость"), 1.0);
	parametrs[5] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("СКО яркости"), 1.0);
	parametrs[6] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("Среднее отклонение"), 1.0);
	parametrs[7] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("СКО отклонения"), 1.0);
	parametrs[8] = new UiDoubleModelParametr(targetLayout, QString::fromLocal8Bit("СКО изображения"), 1.0);


	isInit_ = true;
	connect(parametrs[0], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_firstCorrelationCoeficients);
	connect(parametrs[1], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_secondCorrelationCoeficients);
	connect(parametrs[2], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_firstSigmaCorrelationCoeficients);
	connect(parametrs[3], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_secondSigmaCorrelationCoeficients);
	connect(parametrs[4], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_meanBrightness);
	connect(parametrs[5], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_skoBrightness);
	connect(parametrs[6], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_meanStdDeviation);
	connect(parametrs[7], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_skoStdDeviation);
	connect(parametrs[8], &UiDoubleModelParametr::updateValue, this, &SimpeltwiceRandomUiBuilder::slot_skoForMainImage);
}

void SimpeltwiceRandomUiBuilder::toDefault()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::toDefault();
		parametrs[0]->setValue(0.7);
		parametrs[1]->setValue(0.7);
		parametrs[2]->setValue(0.1);
		parametrs[3]->setValue(0.1);
		parametrs[4]->setValue(0.8);
		parametrs[5]->setValue(0.1);
		parametrs[6]->setValue(0.8);
		parametrs[7]->setValue(0.1);
		parametrs[8]->setValue(0.3);
	}
}

void SimpeltwiceRandomUiBuilder::clearForm()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::clearForm();
		for (auto& param : parametrs)
		{
			delete param;
		}
		isInit_ = false;
	}
}

void SimpeltwiceRandomUiBuilder::setModel(IModelParametrs* modelParametrs)
{
	BaseModelParametrsUiBilder::modelParametrs_ = modelParametrs;
	modelParametrs_ = dynamic_cast<SimpelTwiceRandomModelParametrs*>(modelParametrs);
}

void SimpeltwiceRandomUiBuilder::slot_firstCorrelationCoeficients(double newValue)
{
	modelParametrs_->correlationCoeficients[0] = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_secondCorrelationCoeficients(double newValue)
{
	modelParametrs_->correlationCoeficients[1] = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_firstSigmaCorrelationCoeficients(double newValue)
{
	modelParametrs_->sifmaForCorrelationCoeficients[0] = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_secondSigmaCorrelationCoeficients(double newValue)
{
	modelParametrs_->sifmaForCorrelationCoeficients[1] = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_meanBrightness(double newValue)
{
	modelParametrs_->meanBrightness = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_skoBrightness(double newValue)
{
	modelParametrs_->skoBrightness = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_meanStdDeviation(double newValue)
{
	modelParametrs_->meanStdDeviation = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_skoStdDeviation(double newValue)
{
	modelParametrs_->skoStdDeviation = newValue;
}

void SimpeltwiceRandomUiBuilder::slot_skoForMainImage(double newValue)
{
	modelParametrs_->skoForMainImage = newValue;
}


