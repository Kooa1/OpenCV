//
// Created by 吴文泽 on 2025/10/20.
//

#include "grabcut.h"

GrabCutSample::GrabCutSample() {
    cout << "init\n";
}

void GrabCutSample::draw(string infile) {
    cv::Mat src_file = cv::imread(infile);
    cv::Mat mask, bg_model, fg_model;
    cv::Rect rect(cv::Point(200, 0), cv::Point(src_file.cols - 200, src_file.rows));
    cv::grabCut(src_file,
                mask,
                rect,
                bg_model,
                fg_model,
                10,
                cv::GC_INIT_WITH_RECT);

    cv::rectangle(src_file, rect, cv::Scalar(255), 2, 8);

    cv::imshow("src", src_file);
    cv::imshow("mask", (mask & 1) * 255);
    // cv::imshow("bg", bg_model);
    // cv::imshow("fg", fg_model);

    cv::waitKey(0);
}
