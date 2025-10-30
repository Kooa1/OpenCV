//
// Created by 吴文泽 on 2025/10/28.
//

#ifndef OPENCV_HISTOGRAM_H
#define OPENCV_HISTOGRAM_H

#include <iostream>
#include <vector>
#include <opencv2//opencv.hpp>

using namespace std;

class Histogram {
public:
    explicit Histogram(const string &infile);

    void grey_histogram();

    void matching_histogram(const string &path);

    cv::Mat make_histogram(cv::Mat hist);

private:
    string infile_path;
};


#endif //OPENCV_HISTOGRAM_H
