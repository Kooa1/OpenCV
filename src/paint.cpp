//
// Created by 66 on 2025/10/22.
//

#include "paint.h"

Paint::Paint() {
    cout << "init\n";
}

void Paint::line() {
    cv::Mat m(600, 400, CV_8UC4);
    m.zeros(600, 400, CV_8UC4);

    cv::line(m, cv::Point(100, 100), cv::Point(300, 500), cv::Scalar(0, 0, 255, 10), 5, -1);

    cv::imshow("line", m);
    cv::waitKey(0);
}

void Paint::rect() {
    cv::Mat m(600, 400, CV_8UC4);
    m.zeros(600, 400, CV_8UC4);

    cv::rectangle(m, cv::Point(100, 100), cv::Point(500, 300), cv::Scalar(0, 0, 255, 10), 5);

    cv::imshow("rect", m);
    cv::waitKey(0);
}

void Paint::circle() {
    cv::Mat m(600, 400, CV_8UC4);
    m.zeros(600, 400, CV_8UC4);

    cv::circle(m, cv::Point(100, 100), 50, cv::Scalar(0, 0, 255, 10), 1);

    cv::imshow("rect", m);
    cv::waitKey(0);
}
