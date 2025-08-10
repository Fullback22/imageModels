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
	targetLayout.addWidget(field);


	spBox_medium->setMaximum(255);
	spBox_step->setMaximum(25);
	spBox_quantityColors->setMaximum(255);
	spBox_quantityColors->setMinimum(1);

	isInit_ = true;
	connect(spBox_medium, qOverload<int>(&QSpinBox::valueChanged), this, &MarkovUiBilder::slot_updateMedium);
	connect(spBox_step, qOverload<int>(&QSpinBox::valueChanged), this, &MarkovUiBilder::slot_updateStep);
	connect(spBox_quantityColors, qOverload<int>(&QSpinBox::valueChanged), this, &MarkovUiBilder::slot_updateQuantityColors);
	connect(field, &ProbabilitiesFieldWidget::fieldValuesChanged, this, &MarkovUiBilder::slot_updateConditionalTransitions);

	toDefault();
}

void MarkovUiBilder::toDefault()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::toDefault();
		spBox_medium->setValue(100);
		spBox_step->setValue(5);
		spBox_quantityColors->setValue(5);
		field->oneInit();
	}
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
	BaseModelParametrsUiBilder::modelParametrs_ = modelParametrs;
	modelParametrs_ = dynamic_cast<MarkovModelParametrs*>(modelParametrs);
}

bool MarkovUiBilder::parametrsIsCorrect() const
{
	if(field->fieldIsCorrect())
		return true;
	return false;
}

void MarkovUiBilder::slot_updateStep(int newValue)
{
	modelParametrs_->step = newValue;
}

void MarkovUiBilder::slot_updateQuantityColors(int newValue)
{
	fieldIsResize = true;
	if (newValue >= 1)
	{
		field->resize(newValue);
		modelParametrs_->quantityColors = newValue;
	}
	fieldIsResize = false;
	field->getField(modelParametrs_->conditionalTransitions);
}

void MarkovUiBilder::slot_updateConditionalTransitions()
{
	if (!fieldIsResize)
		field->getField(modelParametrs_->conditionalTransitions);
}

void MarkovUiBilder::slot_updateMedium(int newValue)
{
	modelParametrs_->medium = newValue;
}

