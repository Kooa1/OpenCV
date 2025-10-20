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
    cv::Rect rect(cv::Point(300, 0), cv::Point(src_file.cols - 300, src_file.rows));
    cv::grabCut(src_file,
                mask,
                rect,
                bg_model,
                fg_model,
                20,
                cv::GC_INIT_WITH_RECT);

    cv::rectangle(src_file, rect, cv::Scalar(255), 2, 8);

    cv::imshow("src", src_file);
    cv::imshow("mask", (mask & 1) * 255);
    cv::Mat result_mask = (mask & 1) * 255;

    cv::Mat result_image = cv::Mat(src_file.rows, src_file.cols, CV_8UC3);
    // cv::Mat result_image;
    // cv::resize(result_image, result_image, cv::Size(src_file.rows, src_file.cols));
    for (int i = 0; i < src_file.rows; ++i) {
        for (int j = 0; j < src_file.cols; ++j) {
            cv::Vec3b &pixel_src = src_file.at<cv::Vec3b>(i, j);
            cv::Vec3b &pixel_result = result_image.at<cv::Vec3b>(i, j);

            uchar &pixel_mask = result_mask.at<uchar>(i, j);
            if (pixel_mask == 255) {
                for (int k = 0; k < 3; ++k) {
                    pixel_result[k] = pixel_src[k];
                }
            }
        }
    }

    cv::imshow("result", result_image);

    cv::waitKey(0);
}
