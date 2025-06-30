#include "ImageGenerator.h"

ImageGenerator::ImageGenerator(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    
   /* test.setModel(&gParms);
    test.creatUi(*(ui.vertLayout_modelGrBox));
    test.toDefault();*/
    
    int s{ ui.vertLayout_modelGrBox->count() };
    //setLayout(ui.vertLayout_modelGrBox);
    
    connect(ui.cb_models, qOverload<int>(&QComboBox::currentIndexChanged), this, &ImageGenerator::slot_changeModel);
}

ImageGenerator::~ImageGenerator()
{
}

void ImageGenerator::slot_changeModel(int i)
{
    mainUiBilder->clear();
    mainUiBilder = bilders[i];
    mainUiBilder->setModel(&gParms);
    mainUiBilder->creatUi(*(ui.vertLayout_modelGrBox));
    mainUiBilder->toDefault();
}

