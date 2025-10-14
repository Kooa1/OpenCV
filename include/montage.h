//
// Created by 吴文泽 on 2025/10/14.
//

#ifndef OPENCV_MONTAGE_H
#define OPENCV_MONTAGE_H

#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>

using namespace std;

class Montage {
public:
    explicit Montage();

    void montage(int count);

private:
    int image_count;

    vector<cv::Mat> source_images;
};


#endif //OPENCV_MONTAGE_H
