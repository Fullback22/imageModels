#pragma once
#include <qwidget.h>
#include <qlayout.h>
#include <qspinbox.h>
#include <qlabel.h>

class UiIntModelParametr:public QWidget
{
	Q_OBJECT
		
	QLabel* labelForName{};
	QSpinBox* spBoxForValue{};
	QHBoxLayout* horLayout{};

public:
	UiIntModelParametr(QVBoxLayout& targetLayout, const QString& name, const int maxValue, const int minValue = 1, QWidget* parent = nullptr);
	~UiIntModelParametr();
	int getValue() const;
	void setValue(int const newValue);

signals:
	void updateValue(int newValue);

private slots:
	void slot_changeValue(int value);
};

