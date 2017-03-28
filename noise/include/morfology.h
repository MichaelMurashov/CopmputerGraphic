#ifndef NOISE_MORFOLOGY_H
#define NOISE_MORFOLOGY_H

#include <opencv2/imgproc.hpp>

using namespace cv;

const size_t SIZE_OF_MASK = 3;

namespace Morfology {
    Mat erosion(const Mat &img);  // сужение
    Mat dilation(const Mat &img);  // расширение

    Mat closing(const Mat &img);  // закрытие
    Mat opening(const Mat &img);  // открытие

    static int _mask[SIZE_OF_MASK][SIZE_OF_MASK] = {{1, 1, 1},
                                                    {1, 1, 1},
                                                    {1, 1, 1}};
}

#endif //NOISE_MORFOLOGY_H
