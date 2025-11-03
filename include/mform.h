//
// Created by 吴文泽 on 2025/11/3.
//

#ifndef OPENCV_MFORM_H
#define OPENCV_MFORM_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class MForm {
public:
    explicit MForm(const string &file_path);

    void corrupt();

private:
    string file_path;
};


#endif //OPENCV_MFORM_H