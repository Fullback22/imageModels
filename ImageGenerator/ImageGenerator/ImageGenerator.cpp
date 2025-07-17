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
    std::uniform_int_distribution<int> rotateAndel_dis{ 0,359 };
    std::uniform_int_distribution<int> objSize_dis{ ui.spinBox_minSizeObject->value(),ui.spinBox_maxSizeObject->value() };
    
    cv::Mat maskForObjects{ image.size(), CV_8UC1, cv::Scalar(0) };
    cv::Mat maskObjects(image.size(), CV_8UC1, cv::Scalar(255));
    cv::Mat imageWithObjects{ image.size(), CV_8UC1, cv::Scalar(0) };
    for (size_t i{}; i < ui.spinBox_quantityObjects->value(); ++i)
    {
        int rotateAngel{ 0 };
        if (ui.chBox_rotateObject->isChecked())
        {
            rotateAngel = rotateAndel_dis(generator);
        }
        int objectSize{ objSize_dis(generator) };
        cv::RotatedRect drawRect{ cv::Point(100, 100), cv::Size(objectSize, objectSize), static_cast<float>(rotateAngel) };
        cv::Rect boundingRect{ drawRect.boundingRect() };
        drawRect.center = getCenterXY(image.size(), boundingRect.size());
        boundingRect = drawRect.boundingRect();

        cv::Point2f rectangelPoints_bufer[4];
        drawRect.points(rectangelPoints_bufer);
        std::vector<std::vector<cv::Point>> rectangels{ 4 };
        std::vector<cv::Point> rectangelPoints{ 4 };
        for (int i = 0; i < 4; ++i)
            rectangelPoints[i] = rectangelPoints_bufer[i];
        rectangels.push_back(rectangelPoints);

        mainModel->setParametrs(mainObjectParamert);
        
        cv::fillPoly(maskForObjects, rectangels.back(), 255);

        if (ui.chBox_monochromeObject->isChecked())
        {
            int color{ mainModel->getMainObjectColor(ui.spinBox_contrast->value()) };
            cv::fillPoly(maskObjects, rectangels.back(), color);
        }
        else
        {
            mainObjectParamert->imageWidth = boundingRect.width;
            mainObjectParamert->imageHeigth = boundingRect.height;
            cv::Mat object{};
            mainModel->generateImage(object);
            object.copyTo(maskObjects(boundingRect));
        }
    }
    
    cv::bitwise_and(maskObjects, maskForObjects, maskObjects);
    cv::bitwise_not(maskForObjects, maskForObjects);
    cv::bitwise_and(image, maskForObjects, image);
    cv::bitwise_or(image, maskObjects, image);
    mainModel->setParametrs(mainBackgroundParamert);
}

cv::Point ImageGenerator::getCenterXY(const cv::Size& imageSize, const cv::Size boundingSize)
{
    std::random_device rd{};
    std::mt19937 generator{ rd() };
    int widthOffset{ static_cast<int>(ceil(boundingSize.width / 2.0)) };
    int heightOffset{ static_cast<int>(ceil(boundingSize.height / 2.0)) };
    std::uniform_int_distribution<int> x_dis{ widthOffset, imageSize.width - widthOffset };
    std::uniform_int_distribution<int> y_dis{ widthOffset, imageSize.height - widthOffset };

    return cv::Point(x_dis(generator),y_dis(generator));
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
        addObject(image, savePath_);
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

