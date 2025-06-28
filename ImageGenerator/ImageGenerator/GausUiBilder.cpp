#include "GausUiBilder.h"

GausUiBilder::~GausUiBilder()
{
	delete label_medium;
	label_medium = nullptr;
}

void GausUiBilder::creatUi(QVBoxLayout& targetLayout)
{
	horLayout_medium = new QHBoxLayout(this);
	label_medium = new QLabel();
	label_medium->setText(QString::fromLocal8Bit("Среднее"));
	label_medium->show();
	horLayout_medium->addWidget(label_medium);
	spBox_medium = new QSpinBox();
	horLayout_medium->addWidget(spBox_medium);
	//horLayout_medium->setStretch(0, 1);
	targetLayout.addItem(horLayout_medium);


	label_sko = new QLabel(this);
	label_sko->setText(QString::fromLocal8Bit("СКО"));
	
	
}
