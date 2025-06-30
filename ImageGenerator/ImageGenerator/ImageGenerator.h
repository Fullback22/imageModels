#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImageGenerator.h"

#include "Models/IImageModel.h"
#include "GausUiBilder.h"

class ImageGenerator : public QWidget
{
    Q_OBJECT

public:
    ImageGenerator(QWidget *parent = nullptr);
    ~ImageGenerator();

    GausModelParametrs gParms{};
    //QVector<IImageModel*> models;
    QVector<IModelParametrsUiBilder*> bilders{ new GausUiBilder() };
    IModelParametrsUiBilder* mainUiBilder{};
private:
    Ui::ImageGeneratorClass ui;


private slots:
    void slot_changeModel(int i);
};

