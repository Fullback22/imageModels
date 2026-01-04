#pragma once

#include <QtWidgets/QWidget>
#include <qpixmap.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qfiledialog.h>
#include <qdir.h>
#include "ui_ImageGenerator.h"
#include <qmessagebox.h>

#include "Models/GausModel.h"
#include "Models/MarkovModel.h"
#include "Models/GibsModel.h"
#include "Models/WaveModel.h"
#include "Models/SimpelTwiceRandomModel.h"
#include "Models/UIBuilders/GausUiBilder.h"
#include "Models/UIBuilders/MarkovUiBilder.h"
#include "Models/UIBuilders/GibsUiBilder.h"
#include "Models/UIBuilders/WaveUiBuilder.h"
#include "Models/UIBuilders/SimpeltwiceRandomUiBuilder.h"


class ImageGenerator : public QWidget
{
    enum class Models
    {
        Gaus = 0,
        Markov = 1,
        Gibs = 2,
        WaveModel = 3,
        SimpeltwiceRandomUiBuilder = 4,
        MaxValue = 5
    };
    struct modelData
    {
        QString name{};
        IImageModel* model{};
        IModelParametrsUiBilder* builder{};
        IModelParametrs* backgroundParametr{};
        IModelParametrs* objectParametr{};
    };

    Q_OBJECT

    QString savePath_{};
    bool generationInProgress_{ false };
    QVector<modelData> models;
    IModelParametrsUiBilder* mainUiBilder{};
    IImageModel* mainModel{};
    IModelParametrs* mainBackgroundParamert{};
    IModelParametrs* mainObjectParamert{};

public:
    ImageGenerator(QWidget *parent = nullptr);
    ~ImageGenerator();

private:
    Ui::ImageGeneratorClass ui;

    void showImage(const cv::Mat& image);
    void addObjects(cv::Mat& image, const QString& savePath);
    void addObjects(cv::Mat& image);
    cv::Point getCenterXY(const cv::Size& imageSize, const cv::Size boundingSize);
    void setModel(Models model);

    void createModels();
private slots:
    void slot_changeModel(int i);
    void slot_regenerateImage();
    void slot_toDefualt();
    void slot_openFileDialog();
    void slot_changeSavePath(const QString& str);
    void slot_startGenerate();
};

