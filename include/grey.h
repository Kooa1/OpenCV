//
// Created by 吴文泽 on 2025/10/24.
//

#ifndef OPENCV_GREY_H
#define OPENCV_GREY_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class Grey {
public:
    explicit Grey(const string &file_name);

    void handle();

private:
    string file_path;
};


#endif //OPENCV_GREY_H