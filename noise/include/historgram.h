#ifndef NOISE_GISTORGRAM_H
#define NOISE_GISTORGRAM_H

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace Hist {
    void showHist(const std::string name, const Mat& img) {
        Mat hist;

        int bins = 256;
        int histSize[] = {bins};
        int channels[] = {0};
        float lranges[] = {0, 255};
        const float* ranges[] = {lranges};

        calcHist(&img, 1, channels, Mat(), hist, 1, histSize, ranges);

        double max_val = 0;
        minMaxLoc(hist, 0, &max_val);

        int hist_h = 256;
        Mat imgHist(hist_h, bins, CV_8U);

        for(int i = 0; i < bins; i++) {
            line(imgHist, Point(i, hist_h - cvRound(hist.at<float>(i) * hist_h / max_val)),
                 Point(i, hist_h), Scalar::all(255));
        }

        imshow(name, imgHist);
    }
}

#endif //NOISE_GISTORGRAM_H
