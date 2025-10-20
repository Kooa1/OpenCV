//
// Created by 吴文泽 on 2025/10/20.
//

#ifndef OPENCV_GRABOUT_H
#define OPENCV_GRABOUT_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class GrabOut {
public:
    explicit GrabOut();

    void draw(string infile);
};


#endif //OPENCV_GRABOUT_H
