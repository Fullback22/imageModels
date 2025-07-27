#include "GausUiBilder.h"

GausUiBilder::~GausUiBilder()
{
	clearForm();
}

void GausUiBilder::creatUi(QVBoxLayout& targetLayout)
{
	BaseModelParametrsUiBilder::creatUi(targetLayout);
	horLayout_medium = new QHBoxLayout();
	targetLayout.addLayout(horLayout_medium);

	label_medium = new QLabel(QString::fromLocal8Bit("Ñðåäíåå"));
	horLayout_medium->addWidget(label_medium);
	spBox_medium = new QSpinBox();
	horLayout_medium->addWidget(spBox_medium);

	horLayout_sko = new QHBoxLayout();
	targetLayout.addLayout(horLayout_sko);

	label_sko = new QLabel(QString::fromLocal8Bit("ÑÊÎ"));
	horLayout_sko->addWidget(label_sko);
	spBox_sko = new QSpinBox();
	horLayout_sko->addWidget(spBox_sko);
	isInit_ = true;

	spBox_medium->setMaximum(255);
	spBox_sko->setMaximum(90);

	connect(spBox_medium, qOverload<int>(& QSpinBox::valueChanged), this, &GausUiBilder::slot_updateMedium);
	connect(spBox_sko, qOverload<int>(& QSpinBox::valueChanged), this, &GausUiBilder::slot_updateSko);
}

void GausUiBilder::toDefault()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::toDefault();
		spBox_medium->setValue(100);
		spBox_sko->setValue(5);
	}
}

void GausUiBilder::clearForm()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::clearForm();
		label_medium->hide();
		spBox_medium->hide();
		horLayout_medium->removeWidget(label_medium);
		horLayout_medium->removeWidget(spBox_medium);
		delete label_medium;
		label_medium = nullptr;
		delete spBox_medium;
		spBox_medium = nullptr;
		delete horLayout_medium;
		horLayout_medium = nullptr;

		label_sko->hide();
		spBox_sko->hide();
		horLayout_sko->removeWidget(label_sko);
		horLayout_sko->removeWidget(spBox_sko);
		delete label_sko;
		label_sko = nullptr;
		delete spBox_sko;
		spBox_sko = nullptr;
		delete horLayout_sko;
		horLayout_sko = nullptr;
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
