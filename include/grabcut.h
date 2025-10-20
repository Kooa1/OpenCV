//
// Created by 吴文泽 on 2025/10/20.
//

#ifndef OPENCV_GRABCUT_H
#define OPENCV_GRABCUT_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class GrabCutSample {
public:
    GrabCutSample();

    void draw(string infile);
};


#endif //OPENCV_GRABCUT_H