#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    Mat img = imread("image.jpg", IMREAD_GRAYSCALE);



    imshow("image", img);
    waitKey(0);
    return 0;
}