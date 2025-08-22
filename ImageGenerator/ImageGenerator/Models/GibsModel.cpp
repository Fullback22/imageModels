#include "GibsModel.h"

void GibsModel::generateImage(cv::Mat& inOutImage)
{
}

void GibsModel::setParametrs(IModelParametrs* parametrs)
{
    param_ = dynamic_cast<GibsModelParametrs*>(parametrs);
}

void GibsModel::computeParametrsForObject(IModelParametrs* parametrs, float contrast)
{
}

int GibsModel::getMainObjectColor(float contrast)
{
    return 0;
}
