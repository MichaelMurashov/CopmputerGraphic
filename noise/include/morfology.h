#ifndef NOISE_MORFOLOGY_H
#define NOISE_MORFOLOGY_H

#include <opencv2/opencv.hpp>

using namespace cv;

const size_t SIZE = 3;

namespace Morfology {
    Mat erosion(const Mat& img);  // сужение
    Mat dilation(const Mat& img);  // расширение

    Mat closing(const Mat& img);  // закрытие
    Mat opening(const Mat& img);  // открытие

    static int _mask[SIZE][SIZE] = {{1,1,1},
                                    {1,1,1},
                                    {1,1,1}};
};

#endif //NOISE_MORFOLOGY_H
