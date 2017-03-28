#ifndef NOISE_NOISE_H
#define NOISE_NOISE_H

#include <opencv2/imgproc.hpp>

using cv::Mat;

namespace Noise {
    Mat erlangNoise(const Mat &img, const int barrier);
}

#endif //NOISE_NOISE_H
