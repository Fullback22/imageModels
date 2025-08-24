#include "GibsUiBilder.h"

GibsUiBilder::~GibsUiBilder()
{
	clearForm();
}

void GibsUiBilder::creatUi(QVBoxLayout& targetLayout)
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

	horLayout_quantityIteration = new QHBoxLayout();
	targetLayout.addLayout(horLayout_quantityIteration);

	label_quantityIteration = new QLabel(QString::fromLocal8Bit("Число иттераций"));
	horLayout_quantityIteration->addWidget(label_quantityIteration);
	spBox_quantityIteration = new QSpinBox();
	horLayout_quantityIteration->addWidget(spBox_step);

	horLayout_quantityColors = new QHBoxLayout();
	targetLayout.addLayout(horLayout_quantityColors);

	label_quantityColors = new QLabel(QString::fromLocal8Bit("Число цветов"));
	horLayout_quantityColors->addWidget(label_quantityColors);
	spBox_quantityColors = new QSpinBox();
	horLayout_quantityColors->addWidget(spBox_quantityColors);

	field = new ProbabilitiesFieldWidget();
	targetLayout.addWidget(field);

	startFrequenciesField = new ProbabilitiesFieldWidget();
	targetLayout.addWidget(startFrequenciesField);

	spBox_medium->setMaximum(255);
	spBox_step->setMaximum(25);
	spBox_quantityColors->setMaximum(255);
	spBox_quantityColors->setMinimum(1);
	spBox_quantityIteration->setMaximum(1000);
	spBox_quantityIteration->setMinimum(1);

	isInit_ = true;
	connect(spBox_medium, qOverload<int>(&QSpinBox::valueChanged), this, &GibsUiBilder::slot_updateMedium);
	connect(spBox_step, qOverload<int>(&QSpinBox::valueChanged), this, &GibsUiBilder::slot_updateStep);
	connect(spBox_quantityColors, qOverload<int>(&QSpinBox::valueChanged), this, &GibsUiBilder::slot_updateQuantityColors);
	connect(spBox_quantityIteration, qOverload<int>(&QSpinBox::valueChanged), this, &GibsUiBilder::slot_updateQuantityColors);
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

void GibsUiBilder::slot_updateQuantityItterations(int newValue)
{
	modelParametrs_->quaantityIteration = newValue;
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
