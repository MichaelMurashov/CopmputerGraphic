#ifndef BLACK_WHITE_NOISE_H
#define BLACK_WHITE_NOISE_H

#include <opencv2/opencv.hpp>

using cv::Mat;

class Noise {
public:
    Noise(Mat& img);

    Mat getNoiseImg();

private:
    Mat _img;
};

#endif //BLACK_WHITE_NOISE_H
