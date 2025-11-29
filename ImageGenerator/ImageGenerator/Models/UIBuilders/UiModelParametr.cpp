#include "UiModelPArametr.h"

UiModelParametr::UiModelParametr(QVBoxLayout& targetLayout, const QString& name, const int maxValue, const int minValue, QWidget* parent):
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

	connect(spBoxForValue, qOverload<int>(&QSpinBox::valueChanged), this, &UiModelParametr::slot_changeValue);
}

UiModelParametr::~UiModelParametr()
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

int UiModelParametr::getValue() const
{
	if (spBoxForValue != nullptr)
		return spBoxForValue->value();
	else
		return 0;
}

void UiModelParametr::setValue(int const newValue)
{
	if (spBoxForValue != nullptr)
		spBoxForValue->setValue(newValue);
}

void UiModelParametr::slot_changeValue(int value)
{
	emit updateValue(value);
}
