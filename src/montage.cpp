//
// Created by 吴文泽 on 2025/10/14.
//

#include "montage.h"

Montage::Montage()
    : image_count(0) {
    cout << "test\n";
}

void Montage::in_source(const int count, string target_path) {
    image_count = count;
    this->target_path = target_path;
    const string src_path = "/Users/wuwenze/Desktop/photo/";

    out_image = cv::imread(target_path);
    cout << out_image.size << "\n";

    for (int i = 0; i < count; ++i) {
        cv::Mat src_img;
        stringstream ss;
        ss << src_path << i << ".jpeg";
        // cout << ss.str() << '\n';

        src_img = cv::imread(ss.str());
        cv::resize(src_img, src_img, cv::Size(30, 30));
        source_images.push_back(src_img);
    }
    // cv::imshow("first", source_images[0]);

    // cv::waitKey(0);
}

void Montage::out_target(int width, int height) {
    cv::resize(out_image, out_image, cv::Size(width, height));
    cv::Mat montage_image;
    cv::resize(out_image, montage_image, cv::Size(width, height));

    /*
        直方图
        (1) 根据图片信息统计出直方图信息;
        (2) 根据直方图信息进行匹配
        (3) 替换对应位置的图片
    */
    int bins = 128;
    int hist_sizes[] = {bins, bins, bins};
    float range[] = {0, 255};
    const float *ranges[] = {range, range, range};
    int channels[] = {0, 1, 2};

    vector<cv::MatND> hist_list;

    for (int i = 0; i < image_count; ++i) {
        cv::MatND hist_RGB;
        cv::Mat frame;
        source_images[i].copyTo(frame);

        cv::calcHist(&frame,
                     1,
                     channels,
                     cv::Mat(),
                     hist_RGB,
                     3,
                     hist_sizes,
                     ranges,
                     true,
                     false);

        hist_list.push_back(hist_RGB);
    }

    int number_order = 0;
    for (int y = 0; y < height; y = y + 30) {
        for (int x = 0; x < width; x = x + 30) {
            cv::Mat roi_image = montage_image(cv::Rect(x, y, 30, 30));

            cv::MatND hist_roi;
            double match_max = -1;
            cv::calcHist(&roi_image,
                         1,
                         channels,
                         cv::Mat(),
                         hist_roi,
                         3,
                         hist_sizes,
                         ranges,
                         true,
                         false);

            for (int i = 0; i < image_count; ++i) {
                double match = -1;
                match = cv::compareHist(hist_roi, hist_list[i], cv::HISTCMP_CORREL);

                if (match > match_max) {
                    //将匹配度最高的值算出来
                    number_order = i;
                    match_max = match;
                }
            }

            source_images[number_order].copyTo(roi_image);
        }
    }

    cv::Mat dest_image;
    cv::addWeighted(montage_image, 0.2, out_image, 0.8, 3, dest_image);
    cv::imwrite("/Users/wuwenze/Desktop/photo/desimage.jpeg", dest_image);

    cv::imshow("montage", dest_image);

    cv::waitKey(0);
}
