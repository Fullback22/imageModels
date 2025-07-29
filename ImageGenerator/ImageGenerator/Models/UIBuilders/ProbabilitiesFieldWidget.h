#pragma once

#include <QScrollArea>
#include <qgridlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qvalidator.h>
#include "ui_ProbabilitiesFieldWidget.h"

class ProbabilitiesFieldWidget : public QScrollArea
{
	Q_OBJECT

	
public:
	ProbabilitiesFieldWidget(QWidget *parent = nullptr);
	~ProbabilitiesFieldWidget();
	void resize(size_t const newSize);
	bool fieldIsCorrect() const;
private:
	Ui::ProbabilitiesFieldWidgetClass ui;

	QGridLayout* gridLayout{};
	QWidget* contentWidget{};
	QVector<QVector<QLineEdit*>> le_field{};
	QVector<QLabel*> labelsRowsPosition{};
	QVector<QLabel*> labelsColsPosition{};
	size_t fieldSize{};
	QIntValidator validator{ 1, 100 };
	size_t quantityIncorectLe{};

	void addLineEdit(size_t const x, size_t const y);
	
private slots:
	
signals:
	void fieldChanged();
};
