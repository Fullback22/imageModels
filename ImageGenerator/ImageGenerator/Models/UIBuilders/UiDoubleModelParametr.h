#pragma once
#include <qwidget.h>
#include <qlayout.h>
#include <qdoublespinbox>
#include <qlabel.h>

class UiDoubleModelParametr :public QWidget
{
	Q_OBJECT

	QLabel* labelForName{};
	QDoubleSpinBox* spBoxForValue{};
	QHBoxLayout* horLayout{};

public:
	UiDoubleModelParametr(QVBoxLayout& targetLayout, const QString& name, const double maxValue, const double minValue = 0.0, QWidget* parent = nullptr);
	~UiDoubleModelParametr();
	double getValue() const;
	void setValue(double const newValue);

signals:
	void updateValue(double newValue);

private slots:
	void slot_changeValue(double value);
};

