//
// Created by 吴文泽 on 2025/10/24.
//

#ifndef OPENCV_GREY_H
#define OPENCV_GREY_H

#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;

class Grey {
public:
    explicit Grey(const string &file_name);

    void handle();

    void handle2();

    void line_change();

private:
    string file_path;

    int m_otsu(cv::Mat mat);
};


#endif //OPENCV_GREY_H