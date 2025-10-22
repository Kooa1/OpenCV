//
// Created by 66 on 2025/10/22.
//

#ifndef OPENCV_PAINT_H
#define OPENCV_PAINT_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class Paint {
public:
    explicit Paint();

    void line();

    void rect();

    void circle();
};


#endif //OPENCV_PAINT_H
