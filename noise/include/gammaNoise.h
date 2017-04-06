#ifndef NOISE_GAMMANOISE_H
#define NOISE_GAMMANOISE_H

#include <opencv2/imgproc.hpp>

using cv::Mat;
using cv::Vec3b;

namespace Noise {
    Mat erlangNoise(const Mat &img);
    uchar clamp(double value);
}

#endif //NOISE_GAMMANOISE_H
