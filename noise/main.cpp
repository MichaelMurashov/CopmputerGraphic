#include <opencv2/highgui.hpp>

#include "grayScale.h"
#include "noise.h"
#include "morfology.h"
#include "historgram.h"

int main() {
    Mat img = imread("image.jpg");

    Mat grayImg = GrayScale::intensity(img);
    imshow("qwe", grayImg);
    Hist::showHist(grayImg);

//    Noise noiseImg(grayImg);
//    Mat open = Morfology::closing(img);

    waitKey(0);
    return 0;
}
