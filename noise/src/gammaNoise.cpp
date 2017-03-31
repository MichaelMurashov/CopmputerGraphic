#include <random>
#include <iostream>

#include "gammaNoise.h"

double Noise::genGammaRand() {
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::gamma_distribution<double> distribution(2.0, 4.0);

    return distribution(generator);
}

Mat Noise::erlangNoise(const Mat &img) {
//    Mat result(img.size(), img.type());
//
//    for(int i = 0; i < img.rows; i++)
//        for(int j = 0; j < img.cols; j++) {
//            Vec3b color = img.at<Vec3b>(i, j);
//
//            double num = Noise::genGammaRand();
//
//            double blue = Noise::clamp(color.val[0] + num);
//            double green = Noise::clamp(color.val[1] + num);
//            double red = Noise::clamp(color.val[2] + num);
//
//            result.at<Vec3b>(i, j) = Vec3b(blue, green, red);
//        }
//
//    return result;

    Mat result(img.rows, img.cols, img.type());
    //Mat result = img.clone();
    for (int x = 0; x < img.rows; x++)
    {
        for(int y = 0; y < img.cols; y++)
        {
            std::cout << genGammaRand() << " ";

            Vec3b pixel = img.at<Vec3b>(x, y);
            double coef = genGammaRand();

            uchar blue = clamp(pixel.val[0] + coef);
            uchar green = clamp(pixel.val[1] + coef);
            uchar red = clamp(pixel.val[2] + coef);

            result.at<Vec3b>(x,y) = Vec3b(blue, green, red);
        }
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
