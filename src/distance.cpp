//
// Created by 吴文泽 on 2025/10/29.
//

#include "distance.h"

Distance::Distance(const string &file) {
    cout << "init\n";
    this->file = file;
}

void Distance::change() {
    cv::Mat src_img = cv::imread(this->file);
    cv::Mat grey_img;
    cv::cvtColor(src_img, grey_img, cv::COLOR_RGB2GRAY);

    cv::Mat binary_img;
    cv::threshold(grey_img, binary_img, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    cv::Mat distance;
    cv::distanceTransform(binary_img, distance, cv::DIST_L1, cv::DIST_MASK_3);
    cv::normalize(distance, distance, 0, 1, cv::NORM_MINMAX);

    cv::imshow("src", src_img);
    cv::imshow("grey", grey_img);
    cv::imshow("bin", binary_img);
    cv::imshow("dis", distance);
    cv::waitKey(0);
}
