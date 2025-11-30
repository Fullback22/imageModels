#include "UiIntModelPArametr.h"

UiIntModelParametr::UiIntModelParametr(QVBoxLayout& targetLayout, const QString& name, const int maxValue, const int minValue, QWidget* parent):
	QWidget(parent)
{
	horLayout = new QHBoxLayout();
	targetLayout.addLayout(horLayout);

	labelForName = new QLabel(name);
	horLayout->addWidget(labelForName);
	spBoxForValue = new QSpinBox();
	horLayout->addWidget(spBoxForValue);

	spBoxForValue->setMaximum(maxValue);
	spBoxForValue->setMinimum(minValue);

	connect(spBoxForValue, qOverload<int>(&QSpinBox::valueChanged), this, &UiIntModelParametr::slot_changeValue);
}

UiIntModelParametr::~UiIntModelParametr()
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

int UiIntModelParametr::getValue() const
{
	if (spBoxForValue != nullptr)
		return spBoxForValue->value();
	else
		return 0;
}

void UiIntModelParametr::setValue(int const newValue)
{
	if (spBoxForValue != nullptr)
		spBoxForValue->setValue(newValue);
}

void UiIntModelParametr::slot_changeValue(int value)
{
	emit updateValue(value);
}
