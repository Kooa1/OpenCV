//
// Created by 吴文泽 on 2025/10/28.
//

#include "histogram.h"

Histogram::Histogram(const string &infile) {
    infile_path = infile;
    cout << "init\n";
}

void Histogram::grey_histogram() {
    // 灰度直方图 H-S直方图, RGB直方图
    cv::Mat src_img = cv::imread(infile_path);
    cv::Mat grey_img;
    cv::cvtColor(src_img, grey_img, cv::COLOR_RGB2GRAY);

    // 计算直方图信息
    int channels[1] = {0};
    cv::Mat hist;
    int hist_size[1] = {256};
    float hrange[2] = {0, 255};
    const float *ranges[1] = {hrange};
    cv::calcHist(&grey_img, 1, channels, cv::Mat(), hist, 1, hist_size, ranges);

    // 绘制直方图
    // 直方图均衡化, 将过暗或过亮图片均衡化, 暴露细节
    cv::Mat equal_img;
    cv::equalizeHist(grey_img, equal_img);

    // 彩图均衡化处理
    cv::Mat color_img;
    vector<cv::Mat> BGR_channels;
    cv::split(src_img, BGR_channels);
    for (uint64_t i = 0; i < BGR_channels.size(); ++i) {
        cv::equalizeHist(BGR_channels[i], BGR_channels[i]);
    }

    cv::merge(BGR_channels, color_img);

    cv::imshow("src", src_img);
    cv::imshow("grey", grey_img);
    cv::imshow("out", make_histogram(hist));
    cv::imshow("equal", equal_img);
    cv::imshow("color", color_img);

    cv::waitKey(0);
}

void Histogram::matching_histogram(const string &path) {
    //直方图匹配
    cv::Mat src_img = cv::imread(path);
    cv::resize(src_img, src_img, cv::Size(src_img.cols, src_img.rows));
    cv::Mat grey_img;
    cv::cvtColor(src_img, grey_img, cv::COLOR_RGB2GRAY);

    cv::Mat hist;
    int channels[1] = {0};
    int hist_size[1] = {256};
    float hrange[2] = {0, 255};
    const float *ranges[1] = {hrange};
    cv::calcHist(&grey_img, 1, channels, cv::Mat(), hist, 1, hist_size, ranges);

    cv::Mat new_hist;
    cv::calcHist(&grey_img, 1, channels, cv::Mat(), new_hist, 1, hist_size, ranges);

    // 计算图片累积概率
    float hist_old[256] = {hist.at<float>(0)};
    float hist_new[256] = {new_hist.at<float>(0)};
    for (int i = 0; i < 256; ++i) {
        hist_old[i] = hist_old[i - 1] + hist.at<float>(i);
        hist_new[i] = hist_new[i - 1] + new_hist.at<float>(i);
    }

    // 构建累积概率误差矩阵
    float diff[256][256];
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            diff[i][j] = fabs(hist_old[i] - hist_new[j]);
        }
    }

    // 生成LUT表
    cv::Mat lut(1, 256, CV_8U);
    for (int i = 0; i < 256; ++i) {
        float min = diff[i][0];
        int index = 0;
        for (int j = 1; j < 256; ++j) {
            if (min > diff[i][j]) {
                min = diff[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = static_cast<uchar>(index);
    }

    for (int i = 0; i < 6; ++i) {
        cout << cv::compareHist(hist, new_hist, i) << "\n";
    }

    cv::Mat result_img, hist_out;
    cv::LUT(grey_img, lut, result_img);
    cv::calcHist(&result_img, 1, channels, cv::Mat(), hist_out, 1, hist_size, ranges);

    // cv::imshow("src", src_img);
    cv::imshow("grey_1", grey_img);
    cv::imshow("hist_1", make_histogram(hist));
    cv::imshow("ret_1", result_img);
    cv::imshow("new_1", make_histogram(new_hist));
    cv::imshow("out_1", make_histogram(hist_out));


    cv::waitKey(0);
}

cv::Mat Histogram::make_histogram(cv::Mat hist) {
    cv::Mat output_hist(256, 256, CV_8U, cv::Scalar(255));
    double max_val;
    double min_val;
    cv::minMaxLoc(hist, &min_val, &max_val);
    int hpt = 0.9 * 256;
    for (int i = 0; i < 256; ++i) {
        float bin_val = hist.at<float>(i);
        int temp = static_cast<int>((bin_val * hpt / max_val));
        cv::line(output_hist, cv::Point(i, 256), cv::Point(i, 256 - temp), cv::Scalar::all(0));
    }
    return output_hist;
}
