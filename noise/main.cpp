#include "src/rgbtogray.cpp"
#include "noise.h"

int main() {
    Mat img = imread("image.jpg");
    Mat grayImg = intensity(img);

//    Noise noiseImg(grayImg);



    imshow("qwe", grayImg);
    waitKey(0);

    return 0;
}
