//
// Created by 吴文泽 on 2025/10/14.
//

#include "montage.h"

Montage::Montage()
    : image_count(0) {
    cout << "test\n";
}

void Montage::montage(const int count) {
    image_count = count;

    string file_path = "/Users/wuwenze/Desktop/photo/";

    for (int i = 0; i < count; ++i) {
        cv::Mat src_img;
        stringstream ss;
        ss << file_path << i << ".jpeg";
        cout << ss.str() << '\n';
    }
}
