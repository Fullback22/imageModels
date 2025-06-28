#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImageGenerator.h"

#include "GausUiBilder.h"

class ImageGenerator : public QWidget
{
    Q_OBJECT

public:
    ImageGenerator(QWidget *parent = nullptr);
    ~ImageGenerator();
    GausUiBilder test{};
private:
    Ui::ImageGeneratorClass ui;
};

