#include "morfology.h"

Mat Morfology::erosion(const Mat &img) {
    Mat result(img.rows, img.cols, img.type());
    int radius = SIZE_OF_MASK / 2;

    for(int x = 0; x < img.rows; x++)
        for(int y = 0; y < img.cols; y++) {
            Vec3b min(255, 255, 255);

            for(int i = -radius; i <= radius; i++)
                for(int j = -radius; j <= radius; j++) {
                    Vec3b color = img.at<Vec3b>(clamp(x + i), clamp(y + j));

                    if (_mask[i + radius][j + radius] != 0 &&
                            color.val[0] < min.val[0] && color.val[1] < min.val[1] && color.val[2] < min.val[2])
                        min = color;
                }

            result.at<Vec3b>(x, y) = min;
        }

    return result;
}

Mat Morfology::dilation(const Mat &img) {
    Mat result(img.rows, img.cols, img.type());
    int radius = SIZE_OF_MASK / 2;

    for(int x = 0; x < img.rows; x++)
        for(int y = 0; y < img.cols; y++) {
            Vec3b max(0, 0, 0);

            for(int i = -radius; i <= radius; i++)
                for(int j = -radius; j <= radius; j++) {
                    Vec3b color = img.at<Vec3b>(clamp(x + i), clamp(y + j));

                    if (_mask[i + radius][j + radius] != 0 &&
                            color.val[0] > max.val[0] && color.val[1] > max.val[1] && color.val[2] > max.val[2])
                        max = color;
                }

            result.at<Vec3b>(x, y) = max;
        }

    return result;
}

Mat Morfology::opening(const Mat &img) {
    Mat result = Morfology::erosion(img);
    return Morfology::dilation(result);
}

Mat Morfology::closing(const Mat &img) {
    Mat result = Morfology::dilation(img);
    return Morfology::erosion(result);
}

int Morfology::clamp(int value) {
    if(value < 0)
        return 0;
    else if(value > 255)
        return 255;
    else
        return value;
}
