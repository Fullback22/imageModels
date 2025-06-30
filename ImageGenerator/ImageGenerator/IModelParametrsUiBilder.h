#pragma once
#include <qwidget.h>
#include <qlayout.h>
#include "Models/Parametrs/IModelParametrs.h"

class IModelParametrsUiBilder:public QWidget
{
public:
	virtual ~IModelParametrsUiBilder() {};
	virtual void creatUi(QVBoxLayout& targetLayout) = 0;
	virtual void toDefault() = 0;
	virtual void clear() = 0;
	virtual void setModel(IModelParametrs* modelParametrs) = 0;
};

