//
// Created by 吴文泽 on 2025/11/6.
//

#include "edgedetection.h"

EdgeDetection::EdgeDetection(const string &file_path) {
    src_img = cv::imread(file_path);
    cout << "init\n";
}

void EdgeDetection::detection() {
#if 0 // sobel 算子
    cv::Mat sobel_x, sobel_y;
    cv::Sobel(src_img, sobel_x, CV_8U, 1, 0, 3, 1, 1, cv::BORDER_DEFAULT);

    cv::Sobel(src_img, sobel_y, CV_8U, 1, 0, 3, 1, 1, cv::BORDER_DEFAULT);

    cv::Mat sobel_all;
    cv::Sobel(src_img, sobel_all, CV_8U, 1, 1, 3, 1, 1, cv::BORDER_DEFAULT);

    cv::Mat sobel_out;
    addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, sobel_out);


    cv::imshow("x", sobel_x);
    cv::imshow("y", sobel_y);
    cv::imshow("all", sobel_all);
    cv::imshow("out", sobel_out);
#endif

#if 1 // laplacian
    cv::Mat laplacian_tmp;
    cv::Laplacian(src_img, laplacian_tmp, CV_16S, 3);
    cv::Mat laplacian_img;
    cv::convertScaleAbs(laplacian_tmp, laplacian_img);

    cv::imshow("lap", laplacian_img);

#endif

    cv::imshow("src", src_img);
    cv::waitKey(0);
}
