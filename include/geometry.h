//
// Created by 吴文泽 on 2025/10/23.
//

#ifndef OPENCV_GEOMETRY_H
#define OPENCV_GEOMETRY_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class Geometry {
public:
    explicit Geometry(const string &infile);

    void translate();

    void scale();

    void rotate();

private:
    string file_path;

    cv::Mat src_img;
};


#endif //OPENCV_GEOMETRY_H
