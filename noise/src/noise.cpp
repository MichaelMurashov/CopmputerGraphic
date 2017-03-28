#include <random>

#include "noise.h"

double genGammaRand(const int barrier) {
    std::default_random_engine generator;
    std::gamma_distribution<double> distribution(2.0,2.0);



}

Mat Noise::erlangNoise(const Mat &img, const int barrier) {
    Mat result(img.size(), img.type());

    for(int i = 0; i < img.rows; i++)
        for(int j = 0; j < img.cols; i++)
            result.at<double>(i, j) = img.at<double>(i, j) + genGammaRand(barrier);

    return result;
}
