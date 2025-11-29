#pragma once
#include <qwidget.h>
#include <qlayout.h>
#include <qspinbox.h>
#include <qlabel.h>

class UiModelParametr:public QWidget
{
	Q_OBJECT
		
	QLabel* labelForName{};
	QSpinBox* spBoxForValue{};
	QHBoxLayout* horLayout{};

public:
	UiModelParametr(QVBoxLayout& targetLayout, const QString& name, const int maxValue, const int minValue = 1, QWidget* parent = nullptr);
	~UiModelParametr();
	int getValue() const;
	void setValue(int const newValue);

signals:
	void updateValue(int newValue);

private slots:
	void slot_changeValue(int value);
};

