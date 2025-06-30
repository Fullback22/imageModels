#include "BaseModelParametrsUiBilder.h"

void BaseModelParametrsUiBilder::creatUi(QVBoxLayout& targetLayout)
{
	horLayout_width = new QHBoxLayout();
	targetLayout.addLayout(horLayout_width);

	label_width = new QLabel(QString::fromLocal8Bit("Ширина"));
	horLayout_width->addWidget(label_width);
	spBox_width = new QSpinBox();
	horLayout_width->addWidget(spBox_width);

	horLayout_heigth = new QHBoxLayout();
	targetLayout.addLayout(horLayout_heigth);

	label_heigth = new QLabel(QString::fromLocal8Bit("Высота"));
	horLayout_heigth->addWidget(label_heigth);
	spBox_heigth = new QSpinBox();
	horLayout_heigth->addWidget(spBox_heigth);
	isInit_ = true;

	spBox_width->setMaximum(4000);
	spBox_heigth->setMaximum(4000);

	connect(spBox_width, qOverload<int>(&QSpinBox::valueChanged), this, &BaseModelParametrsUiBilder::slot_updateWidth);
	connect(spBox_heigth, qOverload<int>(&QSpinBox::valueChanged), this, &BaseModelParametrsUiBilder::slot_updateHeigth);
}

void BaseModelParametrsUiBilder::toDefault()
{
	if (isInit_)
	{
		spBox_heigth->setValue(460);
		spBox_width->setValue(460);
	}
}

void BaseModelParametrsUiBilder::clear()
{
	if (isInit_)
	{
		label_width->hide();
		spBox_width->hide();
		horLayout_width->removeWidget(label_width);
		horLayout_width->removeWidget(spBox_width);
		delete label_width;
		label_width = nullptr;
		delete spBox_width;
		spBox_width = nullptr;
		delete horLayout_width;
		horLayout_width = nullptr;

		label_heigth->hide();
		spBox_heigth->hide();
		horLayout_heigth->removeWidget(label_heigth);
		horLayout_heigth->removeWidget(spBox_heigth);
		delete label_heigth;
		label_heigth = nullptr;
		delete spBox_heigth;
		spBox_heigth = nullptr;
		delete horLayout_heigth;
		horLayout_heigth = nullptr;
		isInit_ = false;
	}
}

void BaseModelParametrsUiBilder::setModel(IModelParametrs* modelParametrs)
{
	modelParametrs_ = modelParametrs;
}

void BaseModelParametrsUiBilder::slot_updateHeigth(int newValue)
{
	modelParametrs_->imageHeigth = newValue;
}

void BaseModelParametrsUiBilder::slot_updateWidth(int newValue)
{
	modelParametrs_->imageWidth = newValue;
}
