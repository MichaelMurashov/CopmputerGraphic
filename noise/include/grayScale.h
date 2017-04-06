#ifndef NOISE_GRAYSCALE_H
#define NOISE_GRAYSCALE_H

#include <opencv2/imgproc.hpp>

using namespace cv;

namespace GrayScale {
    Mat method_3(Mat &img);
    Mat intensity(Mat &img);
}

#endif //NOISE_GRAYSCALE_H
