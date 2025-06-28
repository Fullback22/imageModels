// correlationInImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "correlation.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    std::string imageName{ "image/myModel/3.png" };
    cv::Mat image{ cv::imread(imageName, cv::ImreadModes::IMREAD_GRAYSCALE) };
    double corSum{};
    //int maxIterator{ image.size().height };
    //for (int i{}; i < maxIterator; ++i)
    //{
    //    //cv::Rect roi(i, 0, 1, image.size().height);
    //    cv::Rect roi(0, i, image.size().width, 1);
    //    cv::Mat corMat{ image(roi) };

    //    corSum += correlationByCoordinate(corMat);
    //}
    //double cor{ corSum / maxIterator };
    cv::Size groupSize{ 3,3 };
    double cor{ correlationByNeighbor(image, groupSize) };

    cv::imshow("test", image);
    cv::waitKey();
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
