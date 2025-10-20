//
// Created by 吴文泽 on 2025/10/20.
//

#include "../include/grabout.h"

ColorGrabOut::ColorGrabOut() {
    cout << "init\n";
}

void ColorGrabOut::draw(string infile) {
    /*
        1、设置需要去除的颜色
        2、对整个图片进行颜色匹配
        3、展示效果
     */

    cv::Mat src_file = cv::imread(infile, 1);
    cout << src_file.channels();

    cv::Vec3b color(0, 255, 0);
    int tempc = 0;

    cv::Mat temp;
    //转换图片,增加透明空间
    cv::cvtColor(src_file, temp, cv::COLOR_BGR2BGRA);

    for (int i = 0; i < src_file.rows; ++i) {
        for (int j = 0; j < src_file.cols; ++j) {
            cv::Vec3b &pixel = src_file.at<cv::Vec3b>(i, j);
            cv::Vec4b &pixel_temp = temp.at<cv::Vec4b>(i, j);

            if (pixel[0] <= 100 && pixel[1] >= 150 && pixel[2] <= 100) {
                tempc = j + 1;
                pixel_temp[3] = 0;
            } else if (tempc == j - 1) {
                pixel_temp[3] = 0;
            }
        }
    }

    cv::imshow("show", temp);
    cv::imwrite("/Users/wuwenze/Desktop/photo/true.png", temp);
    cv::waitKey(0);
}
