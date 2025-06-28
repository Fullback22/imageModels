#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImageGenerator.h"

class ImageGenerator : public QWidget
{
    Q_OBJECT

public:
    ImageGenerator(QWidget *parent = nullptr);
    ~ImageGenerator();

private:
    Ui::ImageGeneratorClass ui;
};

