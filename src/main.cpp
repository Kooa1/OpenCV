#pragma once

#include  <iostream>

#include "montage.h"

int main() {
    Montage m;
    m.in_source(13, "/Users/wuwenze/Desktop/photo/23.jpeg");
    m.out_target(1920, 1080);

    return 0;
}
