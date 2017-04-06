#ifndef NOISE_MORFOLOGY_H
#define NOISE_MORFOLOGY_H

#include <opencv2/imgproc.hpp>

using cv::Mat;
using cv::Vec3b;

const size_t SIZE_OF_MASK = 3;

namespace Morfology {
    Mat erosion(const Mat &img);  // сужение
    Mat dilation(const Mat &img);  // расширение

    Mat closing(const Mat &img);  // закрытие
    Mat opening(const Mat &img);  // открытие

    int clamp(int value, int left, int right);

    static int _mask[SIZE_OF_MASK][SIZE_OF_MASK] = {{1, 1, 1},
                                                    {1, 1, 1},
                                                    {1, 1, 1}};
}

#endif //NOISE_MORFOLOGY_H
