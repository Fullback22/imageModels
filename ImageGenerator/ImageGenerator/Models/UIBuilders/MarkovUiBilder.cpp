#include "MarkovUiBilder.h"

MarkovUiBilder::~MarkovUiBilder()
{
	clearForm();
}

void MarkovUiBilder::creatUi(QVBoxLayout& targetLayout)
{
	BaseModelParametrsUiBilder::creatUi(targetLayout);
	horLayout_medium = new QHBoxLayout();
	targetLayout.addLayout(horLayout_medium);

	label_medium = new QLabel(QString::fromLocal8Bit("Среднее"));
	horLayout_medium->addWidget(label_medium);
	spBox_medium = new QSpinBox();
	horLayout_medium->addWidget(spBox_medium);

	horLayout_step = new QHBoxLayout();
	targetLayout.addLayout(horLayout_step);

	label_step = new QLabel(QString::fromLocal8Bit("Шаг"));
	horLayout_step->addWidget(label_step);
	spBox_step = new QSpinBox();
	horLayout_step->addWidget(spBox_step);
	
	horLayout_quantityColors = new QHBoxLayout();
	targetLayout.addLayout(horLayout_quantityColors);

	label_quantityColors = new QLabel(QString::fromLocal8Bit("Число цветов"));
	horLayout_quantityColors->addWidget(label_quantityColors);
	spBox_quantityColors = new QSpinBox();
	horLayout_quantityColors->addWidget(spBox_quantityColors);

	field = new ProbabilitiesFieldWidget();
	//field->resize(10);
	field->resize(5);
	targetLayout.addWidget(field);


	spBox_medium->setMaximum(255);
	spBox_step->setMaximum(25);
	spBox_quantityColors->setMaximum(255);

	isInit_ = true;
	connect(spBox_medium, qOverload<int>(&QSpinBox::valueChanged), this, &MarkovUiBilder::slot_updateMedium);
	connect(spBox_step, qOverload<int>(&QSpinBox::valueChanged), this, &MarkovUiBilder::slot_updateStep);
	connect(spBox_quantityColors, qOverload<int>(&QSpinBox::valueChanged), this, &MarkovUiBilder::slot_updateQuantityColors);
}

void MarkovUiBilder::toDefault()
{
}

void MarkovUiBilder::clearForm()
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

		label_step->hide();
		spBox_step->hide();
		horLayout_step->removeWidget(label_step);
		horLayout_step->removeWidget(spBox_step);
		delete label_step;
		label_step = nullptr;
		delete spBox_step;
		spBox_step = nullptr;
		delete horLayout_step;
		horLayout_step = nullptr;

		label_quantityColors->hide();
		spBox_quantityColors->hide();
		horLayout_quantityColors->removeWidget(label_quantityColors);
		horLayout_quantityColors->removeWidget(spBox_quantityColors);
		delete label_quantityColors;
		label_quantityColors = nullptr;
		delete spBox_quantityColors;
		spBox_quantityColors = nullptr;
		delete horLayout_quantityColors;
		horLayout_quantityColors = nullptr;

		field->hide();
		delete field;
		field = nullptr;
		isInit_ = false;
	}
}

void MarkovUiBilder::setModel(IModelParametrs* modelParametrs)
{
}

void MarkovUiBilder::slot_updateStep(int newValue)
{
}

void MarkovUiBilder::slot_updateQuantityColors(int newValue)
{
	field->resize(newValue);
}

void MarkovUiBilder::slot_updateMedium(int newValue)
{
}

