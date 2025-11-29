#include "WaveUiBuilder.h"

WaveUiBuilder::~WaveUiBuilder()
{
	clearForm();
}

void WaveUiBuilder::creatUi(QVBoxLayout& targetLayout)
{
	BaseModelParametrsUiBilder::creatUi(targetLayout);
	horLayout_mediumBrignest = new QHBoxLayout();
	targetLayout.addLayout(horLayout_mediumBrignest);

	label_mediumBrignest = new QLabel(QString::fromLocal8Bit("Средняя яркость"));
	horLayout_mediumBrignest->addWidget(label_mediumBrignest);
	spBox_mediumBrignest = new QSpinBox();
	horLayout_mediumBrignest->addWidget(spBox_mediumBrignest);

	horLayout_skoBrignest = new QHBoxLayout();
	targetLayout.addLayout(horLayout_skoBrignest);

	label_skoBrignest = new QLabel(QString::fromLocal8Bit("СКО яркости"));
	horLayout_skoBrignest->addWidget(label_skoBrignest);
	spBox_skoBrignest = new QSpinBox();
	horLayout_skoBrignest->addWidget(spBox_skoBrignest);

	horLayout_mediumRadius = new QHBoxLayout();
	targetLayout.addLayout(horLayout_mediumRadius);

	label_mediumRadius = new QLabel(QString::fromLocal8Bit("Средний радиус"));
	horLayout_mediumRadius->addWidget(label_mediumRadius);
	spBox_mediumRadius = new QSpinBox();
	horLayout_mediumRadius->addWidget(spBox_mediumRadius);

	horLayout_skoRadius = new QHBoxLayout();
	targetLayout.addLayout(horLayout_skoRadius);

	label_skoRadiusm = new QLabel(QString::fromLocal8Bit("СКО радиуса"));
	horLayout_skoRadius->addWidget(label_skoRadiusm);
	spBox_skoRadius = new QSpinBox();
	horLayout_skoRadius->addWidget(spBox_skoRadius);

	horLayout_threshold = new QHBoxLayout();
	targetLayout.addLayout(horLayout_threshold);

	label_threshold = new QLabel(QString::fromLocal8Bit("Порог"));
	horLayout_threshold->addWidget(label_threshold);
	spBox_threshold = new QSpinBox();
	horLayout_threshold->addWidget(spBox_threshold);

	spBox_mediumBrignest->setMaximum(255);
	spBox_skoBrignest->setMaximum(90);

	spBox_mediumRadius->setMaximum(50);
	spBox_skoRadius->setMaximum(15);

	spBox_threshold->setMaximum(100);

	isInit_ = true;

	connect(spBox_mediumBrignest, qOverload<int>(&QSpinBox::valueChanged), this, &WaveUiBuilder::slot_updateMediumBrignest);
	connect(spBox_skoBrignest, qOverload<int>(&QSpinBox::valueChanged), this, &WaveUiBuilder::slot_updateSkoBrignest);
	connect(spBox_mediumRadius, qOverload<int>(&QSpinBox::valueChanged), this, &WaveUiBuilder::slot_updateMediumRadius);
	connect(spBox_skoRadius, qOverload<int>(&QSpinBox::valueChanged), this, &WaveUiBuilder::slot_updateSkoRadius);
	connect(spBox_threshold, qOverload<int>(&QSpinBox::valueChanged), this, &WaveUiBuilder::slot_updateThreshold);
}

void WaveUiBuilder::toDefault()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::toDefault();
		spBox_mediumBrignest->setValue(100);
		spBox_skoBrignest->setValue(20);
		spBox_mediumRadius->setValue(10);
		spBox_skoRadius->setValue(3);
		spBox_threshold->setValue(1);
	}
}

void WaveUiBuilder::clearForm()
{
	if (isInit_)
	{
		BaseModelParametrsUiBilder::clearForm();
		label_mediumBrignest->hide();
		spBox_mediumBrignest->hide();
		horLayout_mediumBrignest->removeWidget(label_mediumBrignest);
		horLayout_mediumBrignest->removeWidget(spBox_mediumBrignest);
		delete label_mediumBrignest;
		label_mediumBrignest = nullptr;
		delete spBox_mediumBrignest;
		spBox_mediumBrignest = nullptr;
		delete horLayout_mediumBrignest;
		horLayout_mediumBrignest = nullptr;

		label_skoBrignest->hide();
		spBox_skoBrignest->hide();
		horLayout_skoBrignest->removeWidget(label_skoBrignest);
		horLayout_skoBrignest->removeWidget(spBox_skoBrignest);
		delete label_skoBrignest;
		label_skoBrignest = nullptr;
		delete spBox_skoBrignest;
		spBox_skoBrignest = nullptr;
		delete horLayout_skoBrignest;
		horLayout_skoBrignest = nullptr;

		label_mediumRadius->hide();
		spBox_mediumRadius->hide();
		horLayout_mediumRadius->removeWidget(label_mediumRadius);
		horLayout_mediumRadius->removeWidget(spBox_mediumRadius);
		delete label_mediumRadius;
		label_mediumRadius = nullptr;
		delete spBox_mediumRadius;
		spBox_mediumRadius = nullptr;
		delete horLayout_mediumRadius;
		horLayout_mediumRadius = nullptr;

		label_skoRadiusm->hide();
		spBox_skoRadius->hide();
		horLayout_skoRadius->removeWidget(label_skoRadiusm);
		horLayout_skoRadius->removeWidget(spBox_skoRadius);
		delete label_skoRadiusm;
		label_skoRadiusm = nullptr;
		delete spBox_skoRadius;
		spBox_skoRadius = nullptr;
		delete horLayout_skoRadius;
		horLayout_skoRadius = nullptr;

		label_threshold->hide();
		spBox_threshold->hide();
		horLayout_threshold->removeWidget(label_threshold);
		horLayout_threshold->removeWidget(spBox_threshold);
		delete label_threshold;
		label_threshold = nullptr;
		delete spBox_threshold;
		spBox_threshold = nullptr;
		delete horLayout_threshold;
		horLayout_threshold = nullptr;

		isInit_ = false;
	}
}

void WaveUiBuilder::setModel(IModelParametrs* modelParametrs)
{
	BaseModelParametrsUiBilder::modelParametrs_ = modelParametrs;
	modelParametrs_ = dynamic_cast<WaveModelParametrs*>(modelParametrs);
}

bool WaveUiBuilder::parametrsIsCorrect() const
{
	return true;
}

void WaveUiBuilder::slot_updateMediumBrignest(int newValue)
{
	modelParametrs_->meanBrightness = newValue;
}

void WaveUiBuilder::slot_updateSkoBrignest(int newValue)
{
	modelParametrs_->skoBrightness = newValue;
}

void WaveUiBuilder::slot_updateMediumRadius(int newValue)
{
	modelParametrs_->meanRadius = newValue;
}

void WaveUiBuilder::slot_updateSkoRadius(int newValue)
{
	modelParametrs_->skoRadius = newValue;
}

void WaveUiBuilder::slot_updateThreshold(int newValue)
{
	modelParametrs_->distThreshold = newValue;
}
