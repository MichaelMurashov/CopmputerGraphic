#include <opencv2/highgui.hpp>

#include "grayScale.h"
#include "noise.h"
#include "morfology.h"

int main() {
    Mat img = imread("image.jpg");
    Mat grayImg = GrayScale::intensity(img);

//    Noise noiseImg(grayImg);

    Mat open = Morfology::closing(img);

    imshow("qwe", open);
    waitKey(0);

    return 0;
}
