//
// Created by 吴文泽 on 2025/11/12.
//

#ifndef OPENCV_ANGULARPOINTDETECTION_H
#define OPENCV_ANGULARPOINTDETECTION_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class AngularPointDetection {
public:
    explicit AngularPointDetection(const string &file_path);

    void detection();

private:
    cv::Mat src_img;
};


#endif //OPENCV_ANGULARPOINTDETECTION_H