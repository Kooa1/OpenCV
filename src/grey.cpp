//
// Created by 吴文泽 on 2025/10/24.
//

#include "grey.h"

Grey::Grey(const string &file_name) {
    file_path = file_name;
}

void Grey::handle() {
    // 读入图片
    const cv::Mat src_img = cv::imread(file_path, 1);
    // 转换为灰度图
    cv::Mat grey_img;
    cv::cvtColor(src_img, grey_img, cv::COLOR_RGB2GRAY);
    // 进行阈值计算
    const int otsu = m_otsu(grey_img);
    cout << otsu << "\n";
    // 通过阈值进行二值化
    cv::Mat result_img = grey_img.clone();
    for (int i = 0; i < grey_img.rows; ++i) {
        for (int j = 0; j < grey_img.cols; ++j) {
            if (grey_img.at<uchar>(i, j) >= otsu) {
                result_img.at<uchar>(i, j) = 255;
            } else {
                result_img.at<uchar>(i, j) = 0;
            }
        }
    }

    cv::imshow("src", src_img);
    cv::imshow("grey", grey_img);
    cv::imshow("ret", result_img);
    cv::waitKey(0);
}

void Grey::handle2() {
    // 固定阈值处理, 全局阈值处理, 针对亮暗区分明显的使用
    cv::Mat src_img = cv::imread(file_path, cv::IMREAD_GRAYSCALE);
    // 填写阈值进行处理, 根据输入的type类型进行阈值处理
    cv::Mat ret_img;
    cv::threshold(src_img, ret_img, 138, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // 自动阈值处理, 前后景区分不明显, 获取轮廓的方式
    cv::Mat adp_ret;
    cv::adaptiveThreshold(src_img, adp_ret, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);


    cv::imshow("src", src_img);
    cv::imshow("ret", ret_img);
    cv::imshow("adp", adp_ret);

    cv::waitKey(0);
}

void Grey::line_change() {
    cv::Mat src_img = cv::imread(file_path);
    cv::Mat grey_img;
    cv::cvtColor(src_img, grey_img, cv::COLOR_RGB2GRAY);

    // 线性函数变换
    int k = 2;
    int b = 20;

    cv::Mat out_img(grey_img.size(), grey_img.type());
    for (int i = 0; i < grey_img.rows; ++i) {
        for (int j = 0; j < grey_img.cols; ++j) {
            out_img.at<uchar>(i, j) = grey_img.ptr<uchar>(i)[j] * k + b;

            // 如果为对比度拉伸技术, 在该for循环内进行多个函数控制
        }
    }

    // 对数函数变换
    cv::Mat log_img = cv::Mat::zeros(grey_img.size(), grey_img.type());
    grey_img.convertTo(log_img, CV_32F);
    log_img = log_img + 1;
    cv::log(log_img, log_img);
    log_img = log_img * 1.3;
    cv::normalize(log_img, log_img, 0, 255, cv::NORM_MINMAX);
    cv::convertScaleAbs(log_img, log_img);

    // gamma校正
    cv::Mat gamma_img = grey_img.clone();
    float gamma_val = 3;
    uchar LUT[256] = {0};
    for (int i = 0; i < 256; ++i) {
        LUT[i] = pow((i / 255.0), gamma_val) * 255.0;
    }
    cv::MatIterator_<uchar> ite = gamma_img.begin<uchar>();
    cv::MatIterator_<uchar> ite_end = gamma_img.end<uchar>();
    for (; ite != ite_end; ++ite) {
        *ite = LUT[(*ite)];
    }


    cv::imshow("gray", grey_img);
    // cv::imshow("out", out_img);
    // cv::imshow("log", log_img);
    cv::imshow("gamma", gamma_img);

    // 灰度比特平面显示
    cv::Mat bits_img[8];
    for (int i = 0; i < 8; ++i) {
        bits_img[i] = grey_img.clone();
    }

    for (int i = 1; i < 8; ++i) {
        for (int n = 0; n < grey_img.rows; ++n) {
            uchar *ptr_src = grey_img.ptr<uchar>(n);
            uchar *ptr_ret = bits_img[i - 1].ptr<uchar>(n);
            for (int j = 0; j < grey_img.cols; ++j) {
                if (ptr_src[j] >= pow(2, i - 1) && ptr_src[j] < pow(2, i)) {
                    ptr_ret[j] = 255;
                } else {
                    ptr_ret[j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < 8; ++i) {
        cv::imshow("level" + to_string(i), bits_img[i]);
    }

    cv::waitKey(0);
}

int Grey::m_otsu(cv::Mat mat) {
    // 初始化
    int rows = mat.rows;
    int cols = mat.cols;
    int sum_pixel[256] = {0};
    float pro_dis[256] = {0};
    int result_threshold = 0;
    // 统计信息
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum_pixel[static_cast<int>(mat.at<uchar>(i, j))]++;
        }
    }
    //计算概率分布
    for (int i = 0; i < 256; ++i) {
        pro_dis[i] = sum_pixel[i] / static_cast<float>(rows * cols);
    }
    // 计算方差
    float all_left, all_right, avg_left, avg_right, temp_left, temp_right, temp_delta;
    float max_delta = 0.0;
    for (int i = 0; i < 255; ++i) {
        all_left = all_right = avg_left = avg_right = temp_left = temp_right = temp_delta = 0;
        for (int j = 0; j < 255; ++j) {
            if (j <= i) {
                all_left += pro_dis[j];
                temp_left += j * pro_dis[j];
            } else {
                all_right += pro_dis[j];
                temp_right += j * pro_dis[j];
            }
        }
        avg_left = temp_left / all_left;
        avg_right = temp_right / all_right;
        temp_delta = static_cast<float>(all_left * all_right * pow((avg_left = avg_right), 2));
        if (temp_delta > max_delta) {
            max_delta = temp_delta;
            result_threshold = i;
        }
    }
    // 计算结果
    return result_threshold;
}
