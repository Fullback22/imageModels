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
#include "Models/UIBuilders/GausUiBilder.h"
#include "Models/UIBuilders/MarkovUiBilder.h"


class ImageGenerator : public QWidget
{
    Q_OBJECT

    QString savePath_{};
    bool generationInProgress_{ false };

    QVector<IImageModel*> models{ new GausModel() };
    QVector<IModelParametrsUiBilder*> bilders{  new GausUiBilder(), new MarkovUiBilder() };
    QVector<IModelParametrs*> backgroundParametrs{ new GausModelParametrs(), new MarkovModelParametrs() };
    QVector<IModelParametrs*> objectParametrs{ new GausModelParametrs(), new MarkovModelParametrs() };
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
    void addObject(cv::Mat& image, const QString& savePath);
    cv::Point getCenterXY(const cv::Size& imageSize, const cv::Size boundingSize);
private slots:
    void slot_changeModel(int i);
    void slot_regenerateImage();
    void slot_toDefualt();
    void slot_openFileDialog();
    void slot_changeSavePath(const QString& str);
    void slot_startGenerate();
};

