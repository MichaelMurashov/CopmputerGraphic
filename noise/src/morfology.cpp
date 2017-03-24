#include "morfology.h"

Mat Morfology::erosion(const Mat &img) {
    Mat result();

    for(int x = SIZE / 2; x < img.cols - SIZE / 2; x++)
        for(int y = SIZE / 2; y < img.rows - SIZE / 2; y++) {
            Vec3b min(255, 255, 255);


            for(int j = -SIZE / 2; j < SIZE / 2; j++)
                for(int i = -SIZE / 2; i < SIZE / 2; i++) {
                    Vec3b pixel = result.at<Vec3b>(x + i, y + j);

                    if (_mask[i + SIZE / 2][j + SIZE / 2] != 0 &&
                            pixel.val[0] < min.val[0] && pixel.val[1] < min.val[1] && pixel.val[2] < min.val[2])
                        min = pixel;
                }


            result.at<Vec3b>(x, y) = min;
        }

    return result;
}

Mat Morfology::dilation(const Mat &img) {
    Mat result = img.clone();

    for(int x = SIZE / 2; x < img.cols - SIZE / 2; x++)
        for(int y = SIZE / 2; y < img.rows - SIZE / 2; y++) {
            Vec3b max(0, 0, 0);


            for(int j = -SIZE / 2; j < SIZE / 2; j++)
                for(int i = -SIZE / 2; i < SIZE / 2; i++) {
                    Vec3b pixel = result.at<Vec3b>(x + i, y + j);

                    if (_mask[i + SIZE / 2][j + SIZE / 2] != 0 &&
                            pixel.val[0] > max.val[0] && pixel.val[1] > max.val[1] && pixel.val[2] > max.val[2])
                        max = pixel;
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
