#include "src/rgbtogray.cpp"
#include "noise.h"
#include "morfology.h"

int main() {
    Mat img = imread("image.jpg");
    Mat grayImg = intensity(img);

//    Noise noiseImg(grayImg);

    Mat open = Morfology::erosion(img);

    imshow("qwe", open);
    waitKey(0);

    return 0;
}
