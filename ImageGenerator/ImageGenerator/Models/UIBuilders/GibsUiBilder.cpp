#include "GibsUiBilder.h"

GibsUiBilder::~GibsUiBilder()
{
}

void GibsUiBilder::creatUi(QVBoxLayout& targetLayout)
{
	BaseModelParametrsUiBilder::creatUi(targetLayout);
	QHBoxLayout* horLayout_medium = new QHBoxLayout(this);
	targetLayout.addLayout(horLayout_medium);

	QLabel* label_medium = new QLabel(QString::fromLocal8Bit("Среднее"), this);
	horLayout_medium->addWidget(label_medium);
	spBox_medium = new QSpinBox(this);
	horLayout_medium->addWidget(spBox_medium);

	QHBoxLayout* horLayout_step = new QHBoxLayout(this);
	targetLayout.addLayout(horLayout_step);

	QLabel* label_step = new QLabel(QString::fromLocal8Bit("Шаг"), this);
	horLayout_step->addWidget(label_step);
	spBox_step = new QSpinBox(this);
	horLayout_step->addWidget(spBox_step);

	QHBoxLayout* horLayout_quantityColors = new QHBoxLayout(this);
	targetLayout.addLayout(horLayout_quantityColors);

	QLabel* label_quantityColors = new QLabel(QString::fromLocal8Bit("Число цветов"), this);
	horLayout_quantityColors->addWidget(label_quantityColors);
	spBox_quantityColors = new QSpinBox(this);
	horLayout_quantityColors->addWidget(spBox_quantityColors);

	field = new ProbabilitiesFieldWidget(this);
	targetLayout.addWidget(field);


	spBox_medium->setMaximum(255);
	spBox_step->setMaximum(25);
	spBox_quantityColors->setMaximum(255);
	spBox_quantityColors->setMinimum(1);

	isInit_ = true;
	connect(spBox_medium, qOverload<int>(&QSpinBox::valueChanged), this, &GibsUiBilder::slot_updateMedium);
	connect(spBox_step, qOverload<int>(&QSpinBox::valueChanged), this, &GibsUiBilder::slot_updateStep);
	connect(spBox_quantityColors, qOverload<int>(&QSpinBox::valueChanged), this, &GibsUiBilder::slot_updateQuantityColors);
	connect(field, &ProbabilitiesFieldWidget::fieldValuesChanged, this, &GibsUiBilder::slot_updateProbobilityMap);

	toDefault();
}

void GibsUiBilder::toDefault()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::toDefault();
		spBox_medium->setValue(100);
		spBox_step->setValue(5);
		spBox_quantityColors->setValue(5);
		field->diagonalInit(5);
	}
}

void GibsUiBilder::clearForm()
{
}

void GibsUiBilder::setModel(IModelParametrs* modelParametrs)
{
	BaseModelParametrsUiBilder::modelParametrs_ = modelParametrs;
	modelParametrs_ = dynamic_cast<GibsModelParametrs*>(modelParametrs);
}

bool GibsUiBilder::parametrsIsCorrect() const
{
	if (field->fieldIsCorrect())
		return true;
	return false;
}

void GibsUiBilder::slot_updateStep(int newValue)
{
	modelParametrs_->step = newValue;
}

void GibsUiBilder::slot_updateQuantityColors(int newValue)
{
	fieldIsResize = true;
	if (newValue >= 1)
	{
		field->resize(newValue);
		modelParametrs_->quantityColors = newValue;
	}
	fieldIsResize = false;
	field->getField(modelParametrs_->propabilityMap);
}

void GibsUiBilder::slot_updateProbobilityMap()
{
	if (!fieldIsResize)
		field->getField(modelParametrs_->propabilityMap);
}

void GibsUiBilder::slot_updateMedium(int newValue)
{
	modelParametrs_->medium = newValue;
}
