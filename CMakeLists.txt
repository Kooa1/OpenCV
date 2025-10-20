cmake_minimum_required(VERSION 3.10)
project(OpenCV)

set(CMAKE_CXX_STANDARD 20)

# 自动查找所有头文件
file(GLOB_RECURSE HEADER_FILES
        "include/*.h"
        "include/*.hpp"
        "include/*.hxx"
        "src/*.h"
        "src/*.hpp"
        "src/*.hxx"
)

# 自动查找所有源文件
file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "src/*.cxx"
        "src/*.cc"
        "src/*.c"
)

if (WIN32)
    set(OpenCV_DIR "D:/src/opencv/build/x64/vc16/lib")
    include_directories("D:/src/opencv/build/include")
    link_directories("D:/src/opencv/build/x64/vc16/lib")

else (APPLE)
    set(OPENCV_ROOT "/opt/homebrew/Cellar/opencv/4.12.0_11")
    include_directories("/opt/homebrew/Cellar/opencv/4.12.0_11/include")
    link_directories("/opt/homebrew/Cellar/opencv/4.12.0_11/lib")

endif ()

find_package(OpenCV REQUIRED)

# 先创建可执行文件目标
add_executable(OpenCV
        ${SOURCE_FILES}
        ${HEADER_FILES}
        picmake.cpp
        picmake.h
)

# 然后在目标创建后设置包含目录
target_include_directories(OpenCV PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(OpenCV ${OpenCV_LIBS})