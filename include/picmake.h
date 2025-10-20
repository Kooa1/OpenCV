//
// Created by 吴文泽 on 2025/10/20.
//

#ifndef OPENCV_PICMAKE_H
#define OPENCV_PICMAKE_H

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;

class PicMake {
public:
    explicit PicMake();

    void change_color(const string &file_path);
};


#endif //OPENCV_PICMAKE_H
