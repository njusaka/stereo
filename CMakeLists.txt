cmake_minimum_required(VERSION 3.7)
include_directories(
/usr/local/include
/home/pi/src/workspace/stereo_1/include 
)

link_directories(
/usr/local/lib
)
add_executable(stereo_1
main.cpp
light_tracking.cpp
)
target_link_libraries(stereo_1
opencv_videoio
opencv_core
opencv_imgproc
opencv_highgui
opencv_calib3d
)
