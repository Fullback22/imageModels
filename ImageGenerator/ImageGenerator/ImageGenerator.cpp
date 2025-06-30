#include "ImageGenerator.h"

ImageGenerator::ImageGenerator(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    
    test.setModel(&gParms);
    test.creatUi(*(ui.vertLayout_modelGrBox));
    test.toDefault();
    
    int s{ ui.vertLayout_modelGrBox->count() };
    //setLayout(ui.vertLayout_modelGrBox);
    
}

ImageGenerator::~ImageGenerator()
{
}

