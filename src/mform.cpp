//
// Created by 吴文泽 on 2025/11/3.
//

#include "mform.h"

MForm::MForm(const string &file_path) {
    cout << "init\n";
    this->file_path = file_path;
}

void MForm::corrupt() {
    cv::Mat src_img = cv::imread(file_path);
    cv::Mat out_img;

    // 定义结构元(卷积核/掩码)
    cv::Mat struct_element =  cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

    // 进行腐蚀操作
    cv::erode(src_img, out_img, struct_element);

    cv::imshow("src", src_img);
    cv::imshow("out", out_img);
    cv::imshow("sl", struct_element);

    cv::waitKey(0);
}
