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
    connect(ui.pb_regenerate, &QPushButton::clicked, this, &ImageGenerator::slot_regenerateImage);
    connect(ui.pb_toDefualt, &QPushButton::clicked, this, &ImageGenerator::slot_toDefualt);
    connect(ui.pb_saveFileDialog, &QPushButton::clicked, this, &ImageGenerator::slot_openFileDialog);
    connect(ui.pb_generate, &QPushButton::clicked, this, &ImageGenerator::slot_startGenerate);

    connect(ui.le_saveWere, &QLineEdit::textChanged, this, &ImageGenerator::slot_changeSavePath);
    
}

ImageGenerator::~ImageGenerator()
{
}

void ImageGenerator::showImage(const cv::Mat& image)
{
    ui.label_firstImage->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_Grayscale8)));
}

void ImageGenerator::addObject(cv::Mat& image, const QString& savePath)
{
    std::random_device rd{};
    std::mt19937 generator{ rd() };
    std::uniform_int_distribution<int> rotateAndel_dis{ 0,259 };
    std::uniform_int_distribution<int> objSize_dis{ ui.spinBox_minSizeObject->value(),ui.spinBox_maxSizeObject->value() };
    
    //std::normal_distribution<float> dist(param_->medium, param_->sko);
    for (size_t i{}; i < ui.spinBox_quantityObjects->value(); ++i)
    {
        int rotateAngel{ 0 };
        if (ui.chBox_rotateObject->isChecked())
        {
            rotateAngel = rotateAndel_dis(generator);
        }
        int objectSize{ objSize_dis(generator) };
        cv::RotatedRect darwRect{ cv::Point(0,0), cv::Size(objectSize, objectSize), rotateAngel };
        if (ui.chBox_monochromeObject->isChecked())
        {

        }
        else
        {

        }
    }
}

void ImageGenerator::slot_regenerateImage()
{
    mainModel->computeParametrsForObject(mainObjectParamert, ui.spinBox_contrast->value());
    cv::Mat image{};
    
    
    mainModel->generateImage(image);
    showImage(image);
}

void ImageGenerator::slot_toDefualt()
{
    mainUiBilder->toDefault();
}

void ImageGenerator::slot_openFileDialog()
{
    savePath_ = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("Выбор папки"));
    ui.le_saveWere->setText(savePath_);
}

void ImageGenerator::slot_changeSavePath(const QString& str)
{
    savePath_ = str;
}

void ImageGenerator::slot_startGenerate()
{
    QDir dir{ savePath_ };
    QStringList files{ dir.entryList({ "*.png" }, QDir::Files) };
    int startNumber{ files.count() };
    setDisabled(true);
    mainModel->computeParametrsForObject(mainObjectParamert, ui.spinBox_contrast->value());
    for (size_t i{}; i < ui.spBox_quantityImage->value(); ++i)
    {
        cv::Mat image{};
        mainModel->generateImage(image);
        showImage(image);
        size_t imageNumber{ startNumber + i };
        QString saveName{ savePath_ + "img_" + QString::number(imageNumber) + ".png" };
        cv::imwrite(saveName.toStdString(), image);
    }
    setEnabled(true);
}

void ImageGenerator::slot_changeModel(int i)
{
    if (mainUiBilder != nullptr)
    {
        mainUiBilder->clear();
    }
    mainUiBilder = bilders[i];
    mainBackgroundParamert = backgroundParametrs[i];
    mainObjectParamert = objectParametrs[i];
    mainModel = models[i];
    mainUiBilder->setModel(mainBackgroundParamert);
    mainModel->setParametrs(mainBackgroundParamert);
    mainUiBilder->creatUi(*(ui.vertLayout_modelGrBox));
    mainUiBilder->toDefault();
}

