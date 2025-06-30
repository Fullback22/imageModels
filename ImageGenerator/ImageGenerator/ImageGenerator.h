#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImageGenerator.h"

#include "Models/GausModel.h"
#include "Models/UIBuilders/GausUiBilder.h"


class ImageGenerator : public QWidget
{
    Q_OBJECT

public:
    ImageGenerator(QWidget *parent = nullptr);
    ~ImageGenerator();

    GausModelParametrs gParms{};
    QVector<IImageModel*> models{ new GausModel() };
    QVector<IModelParametrsUiBilder*> bilders{ new GausUiBilder() };
    QVector<IModelParametrs*> parametrs{ new GausModelParametrs() };
    IModelParametrsUiBilder* mainUiBilder{};
    IImageModel* mainModel{};
    IModelParametrs* mainModelParamert{};

private:
    Ui::ImageGeneratorClass ui;


private slots:
    void slot_changeModel(int i);
};

