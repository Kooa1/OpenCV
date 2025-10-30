//
// Created by 吴文泽 on 2025/10/30.
//

#ifndef OPENCV_FILTERWAVES_H
#define OPENCV_FILTERWAVES_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class FilterWaves {
public:
    explicit FilterWaves(const string &file_path);

    void handle();

    void box_filter();

private:
    string file_path;
};


#endif //OPENCV_FILTERWAVES_H
