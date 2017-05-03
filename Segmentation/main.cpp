#include <iostream>

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int getIntensity(const Mat& image, int x, int y)  {
    Vec3b color = image.at<Vec3b>(x,y);
    return (int)(0.11 * color.val[0] + 0.53 * color.val[1] + 0.36 * color.val[2]);
}

int check(const vector<vector<Vec3b>>& segments, Vec3b intensity) {
    for (int i = 0; i < segments.size(); i++)
        if (segments[i].operator[](0) == intensity)
            return i;

    return -1;
}

int clamp(int value, int min, int max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

int main() {
    Mat src = imread("../images/Unnamed.png");
//    imshow("src", src);

    vector<vector<Vec3b>> segments;
//    int range = 10;

    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++) {
            Vec3b intensity = src.at<Vec3b>(i, j);
            int pos = check(segments, intensity);

            // если такой пиксель найден, прибавляем к площади
            // иначе, создаем новый сегмент и добавляем пиксель
            if (pos != -1) {
                segments[pos].push_back(intensity);
            } else {
                segments.push_back(vector<Vec3b>());
                segments[segments.size() - 1].push_back(intensity);
            }
        }

    vector<int> perimeters;
    for (int i = 0; i < segments.size(); i++) {
        perimeters.push_back(0);

        for (int x = 1; x < src.rows - 1; x++)
            for (int y = 1; y < src.cols - 1; y++) {
                Vec3b source = segments[i].operator[](0);
                Vec3b intensity = src.at<Vec3b>(x, y);

                Vec3b left  = src.at<Vec3b>(x - 1, y);
                Vec3b up    = src.at<Vec3b>(x,     y + 1);
                Vec3b right = src.at<Vec3b>(x + 1, y);
                Vec3b down  = src.at<Vec3b>(x,     y - 1);

                if (intensity == source && (left != source || up != source || right != source || down != source))
                    perimeters[i]++;
            }
    }

    cout << endl << "Размер изображения: " << src.size() << endl
         << "Кол-во сегментов - " << segments.size() << endl
         << "Статистика сегментов:" << endl;

    for (int i = 0; i < segments.size(); i++)
        cout << "   сегмент №" << i << endl
             << "       цвет - " << segments[i].operator[](0) << endl
             << "       площадь - " << segments[i].size() << endl
             << "       периметр - " << perimeters[i] << endl
             << "       компактность - " << (perimeters[i] * perimeters[i]) / segments[i].size() << endl;

//    waitKey(0);
    return 0;
}