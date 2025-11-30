#include "UiDoubleModelParametr.h"

UiDoubleModelParametr::UiDoubleModelParametr(QVBoxLayout& targetLayout, const QString& name, const double maxValue, const double minValue, QWidget* parent):
	QWidget(parent)
{
	horLayout = new QHBoxLayout();
	targetLayout.addLayout(horLayout);

	labelForName = new QLabel(name);
	horLayout->addWidget(labelForName);
	spBoxForValue = new QDoubleSpinBox();
	horLayout->addWidget(spBoxForValue);

	spBoxForValue->setMaximum(maxValue);
	spBoxForValue->setMinimum(minValue);

	connect(spBoxForValue, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &UiDoubleModelParametr::slot_changeValue);
}

UiDoubleModelParametr::~UiDoubleModelParametr()
{
	labelForName->hide();
	spBoxForValue->hide();
	horLayout->removeWidget(labelForName);
	horLayout->removeWidget(spBoxForValue);
	delete labelForName;
	labelForName = nullptr;
	delete spBoxForValue;
	spBoxForValue = nullptr;
	delete horLayout;
	horLayout = nullptr;
}

double UiDoubleModelParametr::getValue() const
{
	return spBoxForValue->value();
}

void UiDoubleModelParametr::setValue(double const newValue)
{
	spBoxForValue->setValue(newValue);
}

void UiDoubleModelParametr::slot_changeValue(double value)
{
	emit updateValue(value);
}
