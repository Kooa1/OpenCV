//
// Created by 吴文泽 on 2025/10/29.
//

#ifndef OPENCV_DISTANCE_H
#define OPENCV_DISTANCE_H

#include <iostream>
#include <opencv2//opencv.hpp>

using namespace std;

class Distance {
public:
    explicit Distance(const string &file);

    void change();

private:
    string file;
};


#endif //OPENCV_DISTANCE_H