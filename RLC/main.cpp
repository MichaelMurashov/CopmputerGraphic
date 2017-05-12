#include <iostream>

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat predict(const Mat& src) {
    Mat result(src.rows, src.cols, src.type());

    for (int i = 0; i < src.cols; i++)
        for (int j = 0; j < src.rows; j++) {
            if (i == 0 && j == 0)
                result.at<int>(0, 0) = 0;
            else if (i == 0 && j == 1)
                result.at<int>(0, 1) = src.at<int>(0, 0) / 2;

            else if (i != 0 && j == 0)
                result.at<int>(i, j) = (src.at<int>(i - 1, src.cols - 2) + src.at<int>(i - 1, src.cols - 1)) / 2;
            else if (i != 0 && j == 1)
                result.at<int>(i, j) = (src.at<int>(i - 1, src.cols - 1) + src.at<int>(i, j - 1)) / 2;
            else
                result.at<int>(i, j) = (src.at<int>(i, j - 2) + src.at<int>(i, j - 1)) / 2;
        }

    return result;
}

Mat error(const Mat& src, const Mat& prediction) {
    Mat result(src.rows, src.cols, CV_32S);

    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++) {
            result.at<int>(i, j) = src.at<int>(i, j) - prediction.at<int>(i, j);
        }

    return result;
}

Mat quantization(const Mat& error, int B) {
    Mat result(error.rows, error.cols, error.type());

    for (int i = 0; i < error.rows; i++)
        for (int j = 0; j < error.cols; j++) {
            int newPixel = error.at<int>(i, j);

            if (newPixel < (-B / 2))
                newPixel = -B;
            else
                if ((-B / 2) <= newPixel && newPixel <= (B / 2))
                    newPixel = 0;
                else
                    newPixel = B;

            result.at<int>(i, j) = newPixel;
        }

    return result;
}

vector<int> RLC(const Mat& quant) {
    vector<int> result;
    int count = 0;

    for (int i = 0; i < quant.rows; i++)
        for (int j = 0; j < quant.cols; j++) {
            int value = quant.at<int>(i, j);

            if (value == 0) {
                count++;
            } else {
                result.push_back(count);
                result.push_back(value);
                count = 0;
            }
        }

    result.push_back(0);
    result.push_back(0);
    return result;
}

int main() {
//    Mat src = imread("", CV_LOAD_IMAGE_GRAYSCALE);

    Mat src(3, 3, CV_32S);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            src.at<int>(i, j) = rand() % 5;

    cout << "Исходная матрица:" << endl << src << endl << endl;

    Mat prediction = predict(src);
    cout << "Предсказание:" << endl << prediction << endl << endl;

    Mat err = error(src, prediction);
    cout << "Ошибка:" << endl << err << endl << endl;

    Mat quant = quantization(err, 2);
    cout << "Квантование:" << endl << quant << endl << endl;

    vector<int> rlc = RLC(quant);
    cout << "RLC" << endl;
    for (int i = 0; i < rlc.size(); i += 2)
        cout << "(" << rlc[i] << ", " << rlc[i+1] << "); ";
    cout << endl;

    return 0;
}
