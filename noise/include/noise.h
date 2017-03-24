#ifndef NOISE_NOISE_H
#define NOISE_NOISE_H

#include <opencv2/imgproc.hpp>

using cv::Mat;

namespace Noise {
    Mat erlangNoise(Mat &img);
}

#endif //NOISE_NOISE_H
