#include "GausUiBilder.h"

GausUiBilder::~GausUiBilder()
{
	clearForm();
}

void GausUiBilder::creatUi(QVBoxLayout& targetLayout)
{
	BaseModelParametrsUiBilder::creatUi(targetLayout);
	parametrs.push_back(new UiIntModelParametr(targetLayout, QString::fromLocal8Bit("Ñðåäíåå"), 255));
	parametrs.push_back(new UiIntModelParametr(targetLayout, QString::fromLocal8Bit("ÑÊÎ"), 90));

	isInit_ = true;
	connect(parametrs[0], &UiIntModelParametr::updateValue, this, &GausUiBilder::slot_updateMedium);
	connect(parametrs[1], &UiIntModelParametr::updateValue, this, &GausUiBilder::slot_updateSko);
}

void GausUiBilder::toDefault()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::toDefault();
		parametrs[0]->setValue(100);
		parametrs[1]->setValue(5);
	}
}

void GausUiBilder::clearForm()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::clearForm();
		for (auto& param : parametrs)
		{
			delete param;
		}
		parametrs.clear();
		isInit_ = false;
	}
}

void GausUiBilder::setModel(IModelParametrs* modelParametrs)
{
	BaseModelParametrsUiBilder::modelParametrs_ = modelParametrs;
	modelParametrs_ = dynamic_cast<GausModelParametrs*>(modelParametrs);
}

void GausUiBilder::slot_updateSko(int newValue)
{
	modelParametrs_->sko = newValue;
}

void GausUiBilder::slot_updateMedium(int newValue)
{
	modelParametrs_->medium = newValue;
}
