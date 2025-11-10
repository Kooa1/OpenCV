//
// Created by 吴文泽 on 2025/11/10.
//

#include "geometrydetection.h"

GeometryDetection::GeometryDetection(const string &file_path) {
    src_img = imread(file_path);
    cvtColor(src_img, gray_img, COLOR_RGB2GRAY);
    cout << "init\n";
}

void GeometryDetection::detection_circles() {
    // (1) 图片预处理, 均衡、灰度化、二值化、降噪、滤波...

    // (2) 使用监测函数, 统计相关的形状信息
    vector<Vec3f> circles; // 圆, 圆心(x, y), 半径r
    /*
        参数三: HOUGH_GRADIENT 霍夫梯度算法
        参数四: 累加器的比值
        参数五: 最小圆心距离
        参数六: 用于第三个参数算法的边缘检测距离
        参数七: 用于第三个参数算法的累加器阈值
     */
    HoughCircles(gray_img, circles, HOUGH_GRADIENT, 1, 10, 80, 80);
    cout << circles.size() << "\n";

    // (3) 收集信息计算...
    Mat out_img = src_img.clone();
    // 将识别出的信息绘制
    for (int i = 0; i < circles.size(); ++i) {
        Point centre(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = circles[i][2];

        circle(out_img, centre, 3, Scalar(0), -1);

        circle(out_img, centre, radius, Scalar(0), 3);
    }

    // imshow("src", src_img);
    imshow("out", out_img);

    waitKey(0);
}

void GeometryDetection::find_contours() {
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    /*
      参数1: 需要是二值图或灰度图, 之前通过阈值处理, canny检测等等产生结果
      参数2: 轮廓的点向量集合, contours.size 轮廓的个数, contours[i].size 轮廓的边数
      参数3: hierarchy 前一个轮廓, 后一个轮廓, 外轮廓, 内轮廓, 如果不存在输出-1
      参数4: 模式
         RETR_EXTERNAL  = 0 只计算外部轮廓
         RETR_LIST      = 1 检测所有轮廓, 所有轮廓存在关系, 是否存在内外关系
         RETR_CCOMP     = 2 检测所有轮廓, 只建立两个等级关系 最外/内
         RETR_TREE      = 3 检测所有轮廓, 建立等级树关系
      参数5: 近似方法
         CHAIN_APPROX_NONE      = 1 保存轮廓上的所有的点
         CHAIN_APPROX_SIMPLE    = 2 只保存拐点信息
     */
    Mat canny_img;
    Canny(gray_img, canny_img, 100, 200 );

    imshow("canny", canny_img);

    findContours(canny_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // cout << contours.size() << '\n';
    // cout << hierarchy.size() << '\n';
    if (hierarchy.size() > 0) {
        cout << hierarchy[0][0] << ", " << hierarchy[1][0] << ", " << hierarchy[2][0] << ", " << hierarchy[3][0] << '\n';
    }

    for (int i = 0; i < contours.size(); ++i) {
        cout << contours[i].size() << "\n";
    }

    Mat out_img = src_img.clone();
    drawContours(out_img, contours, -1, Scalar(0), 5);

    approx_polyPD()

    imshow("out", out_img);
    waitKey(0);
}

void GeometryDetection::approx_polyPD() {

}
