#include "grayScale.h"

Mat GrayScale::method_3(Mat &img) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++) {
            Vec3b color = img.at<Vec3b>(i, j);

            double blue = color.val[0];
            double green = color.val[1];
            double red = color.val[2];

            result.at<Vec3b>(i, j) = Vec3b((uchar)((blue + green + red) / 3), (uchar)((blue + green + red) / 3),
                                           (uchar)((blue + green + red) / 3));
        }

    return result;
}

Mat GrayScale::intensity(Mat &img) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++) {
            Vec3b color = img.at<Vec3b>(i, j);

            double blue = 0.11 * color.val[0];
            double green = 0.53 * color.val[1];
            double red = 0.36 * color.val[2];

            result.at<Vec3b>(i, j) = Vec3b((uchar)(blue + green + red), (uchar)(blue + green + red),
                                           (uchar)(blue + green + red));
        }

    return result;
}