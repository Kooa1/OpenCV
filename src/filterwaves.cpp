//
// Created by 吴文泽 on 2025/10/30.
//

#include "filterwaves.h"

FilterWaves::FilterWaves(const string &file_path) {
    this->file_path = file_path;
}

void FilterWaves::handle() {
    // 读取图片
    cv::Mat src_img = cv::imread(file_path);
    // 创建卷积核(掩码), 如果在滤波中使用, 一般都是3、5、7的值
    cv::Mat kernal = (cv::Mat_<double>(3, 3) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
    // 进行卷积化处理
    cv::Mat ret_img;
    // OpenCV提供了卷积处理函数filter2D
    cv::filter2D(src_img, ret_img, src_img.depth(), kernal);

    cv::imshow("src", src_img);
    cv::imshow("ret", ret_img);

    cv::waitKey(0);
}

void FilterWaves::box_filter() {
    cv::Mat src_img = cv::imread(file_path);
    // 方框滤波(盒滤波)
    cv::Mat box_img;
    cv::boxFilter(src_img, box_img, -1, cv::Size(5, 5), cv::Point(-1, -1), true);

    // 均值滤波 (盒滤波进行归一化处理即为均值滤波)
    cv::Mat blur_img;
    cv::blur(src_img, blur_img, cv::Size(5, 5));

    // 高斯滤波
    cv::Mat gaussian_img;
    cv::GaussianBlur(src_img, gaussian_img, cv::Size(5, 5), 0);

    // median blur 中值滤波 (对于椒盐去噪非常有效)
    cv::Mat median_img;
    cv::medianBlur(src_img, median_img, 3);

    // bilateral filter blur 双边滤波 (针对于普通图片处理, 有一定的美颜效果);
    cv::Mat bilateral_img;
    cv::bilateralFilter(src_img, bilateral_img, 0, 100, 5);

    // 去噪函数
    cv::Mat dns_img;
    cv::fastNlMeansDenoisingColored(src_img, dns_img, 10, 10);

    cv::imshow("src", src_img);
    // cv::imshow("box", blur_img);
    // cv::imshow("blur", blur_img);
    // cv::imshow("gaussian", gaussian_img);
    cv::imshow("med", median_img);
    // cv::imshow("bil", bilateral_img);
    // cv::imshow("dns", dns_img);

    cv::waitKey(0);
}
