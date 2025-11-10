#include "geometrydetection.h"

int main() {
    GeometryDetection g("/Users/wuwenze/Desktop/photo/shapes2.jpg");
    // g.detection_circles();
    g.find_contours();
    // g.approx_polyPD();

    return 0;
}
