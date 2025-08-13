#pragma once

#include <QScrollArea>
#include <qgridlayout.h>
#include <qgridlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qvalidator.h>
#include <qpushbutton.h>
#include <random>
#include "ui_ProbabilitiesFieldWidget.h"

class ProbabilitiesFieldWidget : public QScrollArea
{
	Q_OBJECT

	
public:
	ProbabilitiesFieldWidget(QWidget *parent = nullptr);
	~ProbabilitiesFieldWidget();
	void resize(size_t const newSize);
	bool fieldIsCorrect() const;
	void randomInit();
	void oneInit();
	void diagonalInit(int const diagonalValue);
	void getField(std::vector<std::vector<unsigned int>>& outField);
private:
	Ui::ProbabilitiesFieldWidgetClass ui;

	QGridLayout* gridLayout{};
	QVBoxLayout* mainLayout{};
	QHBoxLayout* buttonLayout{};
	QWidget* contentWidget{};
	QPushButton* pb_random{};
	QVector<QVector<QLineEdit*>> le_field{};
	QVector<QLabel*> labelsRowsPosition{};
	QVector<QLabel*> labelsColsPosition{};
	size_t fieldSize{};
	QIntValidator validator{ 0, 100 };
	size_t quantityIncorectLe{};

	void addLineEdit(size_t const x, size_t const y);
	
private slots:
	void slot_randomGenerate();
	
signals:
	void fieldValuesChanged();
};
