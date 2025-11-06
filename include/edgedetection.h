//
// Created by 吴文泽 on 2025/11/6.
//

#ifndef OPENCV_EDGEDETECTION_H
#define OPENCV_EDGEDETECTION_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class EdgeDetection {
public:
    explicit EdgeDetection(const string &file_path);

    void detection();

private:
    cv::Mat src_img;
};


#endif //OPENCV_EDGEDETECTION_H
