//
// Created by 吴文泽 on 2025/10/23.
//

#include "geometry.h"

Geometry::Geometry(const string &infile) {
    cout << "init\n";
    file_path = infile;
    src_img = cv::imread(file_path, 1);
}

void Geometry::translate() {
    cv::Mat translate1;
    cv::Mat delta = cv::Mat::zeros(2, 3, CV_32FC1);

    delta.at<float>(0, 0) = 1;
    delta.at<float>(1, 1) = 1;
    delta.at<float>(0, 2) = 30;
    delta.at<float>(1, 2) = 50;

    cv::warpAffine(src_img, translate1, delta, src_img.size());

    cv::imshow("src", src_img);
    cv::imshow("translate", translate1);

    cv::waitKey(0);
}

void Geometry::scale() {
}

void Geometry::rotate() {
    cv::Mat delte_rotate = cv::getRotationMatrix2D(cv::Point(src_img.cols / 2, src_img.rows / 2), 45, 1.0);

    cv::Mat rotate;
    cv::warpAffine(src_img, rotate, delte_rotate, src_img.size());

    cv::Point2f src_aff[3] = {cv::Point2f(0, 0), cv::Point2f(src_img.cols / 2, 0), cv::Point2f(0, src_img.rows + 20)};
    cv::Point2f des_aff[3] = {
        cv::Point2f(src_img.cols * 0, src_img.rows * 0.33),
        cv::Point2f(src_img.cols * 0.8, src_img.rows * 0.2),
        cv::Point2f(src_img.cols * 0.4, src_img.rows * 0.7)
    };

    cv::Mat delta_custom = cv::getAffineTransform(src_aff, des_aff);
    cv::Mat custom;
    warpAffine(src_img, custom, delta_custom, src_img.size());

    cv::imshow("src", src_img);
    cv::imshow("translate", custom);

    cv::waitKey(0);
}
