#include <random>
#include <iostream>

#include "gammaNoise.h"

Mat Noise::erlangNoise(const Mat &img) {
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::gamma_distribution<double> distribution(2.0, 4.0);

    Mat result(img.size(), img.type());

    for (int x = 0; x < img.rows; x++)
        for(int y = 0; y < img.cols; y++) {
//            std::cout << genGammaRand() << " ";

            Vec3b pixel = img.at<Vec3b>(x, y);
            double coef = distribution(generator);

            uchar blue = clamp(pixel.val[0] + coef);
            uchar green = clamp(pixel.val[1] + coef);
            uchar red = clamp(pixel.val[2] + coef);

            result.at<Vec3b>(x,y) = Vec3b(blue, green, red);
        }

    return result;
}

uchar Noise::clamp(double value) {
    if(value < 0.0)
        return 0;
    else if(value > 255.0)
        return 255;
    else
        return (uchar)value;

}
