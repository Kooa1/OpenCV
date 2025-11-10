//
// Created by 吴文泽 on 2025/11/10.
//

#ifndef OPENCV_GEOMETRYDETECTION_H
#define OPENCV_GEOMETRYDETECTION_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class GeometryDetection {
public:
    explicit GeometryDetection(const string &file_path);

    void detection_circles();

    void find_contours();

    void approx_polyPD();

private:
    Mat src_img;
    Mat gray_img;
};


#endif //OPENCV_GEOMETRYDETECTION_H
