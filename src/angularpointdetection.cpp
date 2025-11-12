//
// Created by 吴文泽 on 2025/11/12.
//

#include "angularpointdetection.h"

AngularPointDetection::AngularPointDetection(const string &file_path) {
    src_img = cv::imread(file_path);
    cout << "init\n";
}

void AngularPointDetection::detection() {
    // 图像的前处理 滤波, 二值化
    cv::Mat temp_img = src_img.clone();
    cv::Mat gray_img;
    cv::cvtColor(temp_img, gray_img, cv::COLOR_RGB2GRAY);

    cv::Mat out_img;
    cv::cornerHarris(gray_img, out_img, 5, 15, 0.05);

    // cv::Mat normal_img;
    // cv::normalize(out_img, normal_img, 0, 255, cv::NORM_MINMAX, CV_32FC1);

    // cv::Mat after_img;
    // cv::convertScaleAbs(normal_img, after_img);

    // for (int i = 0; i < normal_img.rows; ++i) {
    // for (int j = 0; j < normal_img.cols; ++j) {
    // if (normal_img.at<float>(i, j) > 200) {
    // cv::circle(temp_img, cv::Point(j, i), 5, cv::Scalar(0, 0, 255), 2);
    // }
    // }
    // }

    vector<cv::Point2f> corners;
    double quality = 0.1;
    double min_distance = 10;

    cv::goodFeaturesToTrack(gray_img, corners, 10000, quality, min_distance);
    cout << corners.size() << '\n';

    for (int i = 0; i < corners.size(); ++i) {
        cv::circle(temp_img, corners[i], 5, cv::Scalar(0, 0, 255), 2);
    }

    // cv::imshow("src", src_img);
    // cv::imshow("out", out_img);
    // cv::imshow("nor", normal_img);
    cv::imshow("temp", temp_img);
    // cv::imshow("aft", after_img);

    cv::waitKey(0);
}
