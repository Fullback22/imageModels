#pragma once
class IModelParametrsUiBilder
{
public:
	virtual ~IModelParametrsUiBilder() {};
	virtual void creatUi() = 0;
	virtual void toDefault() = 0;
	virtual void clear() = 0;

};

