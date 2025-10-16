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

    void in_source(int count, string target_path);

    void out_target(int width, int height);

private:
    string target_path;

    int image_count;

    cv::Mat out_image;

    vector<cv::Mat> source_images;
};


#endif //OPENCV_MONTAGE_H
