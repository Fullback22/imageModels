#pragma once
#include "IImageModel.h"
#include "Parametrs/GibsModelParametrs.h"

#include <random>
#include <numeric>

class GibsModel :
    public IImageModel
{
    std::random_device rd_{};
    std::mt19937 generator_{ rd_() };
	cv::Mat mainImage_{};
	
	int getValueFromPropabilityMap(int const firstClass, int const secondClass) const;
	int generateNewValue(const std::vector<int>& ProbabilityDensity);
	std::vector<int> computeProbabilityDensity1(int const x, int const y);
	std::vector<int> computeProbabilityDensity2(int const x, int const y);
	std::vector<int> computeProbabilityDensity3(int const x, int const y);
	std::vector<int> computeProbabilityDensity4(int const x, int const y);
	std::vector<int> computeProbabilityDensity5(int const x, int const y);
	std::vector<int> computeProbabilityDensity6(int const x, int const y);
	std::vector<int> computeProbabilityDensity7(int const x, int const y);
	std::vector<int> computeProbabilityDensity8(int const x, int const y);
	std::vector<int> computeProbabilityDensity9(int const x, int const y);
	void generatePart1();
	void generatePart2();
	void generatePart3();
	void generatePart4();
	void generatePart5();
	void generatePart6();
	void generatePart7();
	void generatePart8();
	void generatePart9();
	void initMainImage();

    GibsModelParametrs* param_{};
public:
    void generateImage(cv::Mat& inOutImage) override;
    void setParametrs(IModelParametrs* parametrs) override;
    void computeParametrsForObject(IModelParametrs* parametrs, float contrast) override;
    int getMainObjectColor(float contrast) override;
};

