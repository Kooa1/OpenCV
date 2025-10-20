//
// Created by 吴文泽 on 2025/10/20.
//

#include "../include/picmake.h"

PicMake::PicMake() {
    cout << "init\n";
}

void PicMake::change_color(const string &file_path) {
    cv::Mat src_file = cv::imread(file_path, cv::IMREAD_UNCHANGED);

    // 颜色空间RGB (1), RGBA(-1), 灰色空间(0)

    //存储阶段颜色值
    vector<cv::Vec3d> colors;
    // uint64_t index = 0;

    unsigned long index = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            for (int k = 0; k < 6; ++k) {
                colors.push_back(cv::Vec3d());
                colors[index][0] = i / 5.0 * 255;
                colors[index][1] = j / 5.0 * 255;
                colors[index][2] = k / 5.0 * 255;
                index++;
            }
        }
    }

    //更改对应的颜色值
    index = 0;
    cv::Mat temp = src_file.clone();
    while (index < colors.size()) {
        for (int r = 0; r < src_file.rows; ++r) {
            for (int c = 0; c < src_file.cols; ++c) {
                //获取单点颜色值
                // cv::Vec4b &pixel = src_file.at<cv::Vec4b>(r, c);
                cv::Vec4b &temp_pixel = temp.at<cv::Vec4b>(r, c);
                //判断透明度是否为0
                if (temp_pixel[3] == 0) {
                    continue;
                } else {
                    for (int i = 0; i < 3; ++i) {
                        temp_pixel[i] = colors[index][i];
                    }
                }
            }
        }
        stringstream ss;
        ss << "/Users/wuwenze/Desktop/photo/p/out_img" << index << index - 1 << index + 1 << ".png";
        cv::imwrite(ss.str(), temp);
        index++;
    }

    //保存需要的图片
}
