#include <opencv2/highgui.hpp>

#include "grayScale.h"
#include "gammaNoise.h"
#include "morfology.h"
#include "historgram.h"

int main() {
    Mat img = imread("image.jpg");

    Mat grayImg = GrayScale::intensity(img);

    Mat noiseImg = Noise::erlangNoise(grayImg);

    imshow("noise", noiseImg);
//    Hist::showHist("noise hist", noiseImg);

//    Mat morfImg = Morfology::closing(noiseImg);
//    imshow("close", morfImg);

    waitKey(0);
    return 0;
}
