//
// Created by 吴文泽 on 2025/10/24.
//

#include "grey.h"

Grey::Grey(const string &file_name) {
    file_path = file_name;
}

void Grey::handle() {
    // 读入图片
    cv::Mat src_img = cv::imread(file_path, 1);
    // 转换为灰度图

    // 进行阈值计算

    // 通过阈值进行二值化


    cv::imshow("src", src_img);

    cv::waitKey(0);
}
