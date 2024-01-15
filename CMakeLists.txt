cmake_minimum_required(VERSION 3.5)

project(ocrCaptchaMnn)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})

add_subdirectory(MNN)

include_directories(MNN/include)
add_executable(ocrCaptchaMnn main.cpp OcrCaptcha.hpp words.h)

target_link_libraries(ocrCaptchaMnn PUBLIC MNN ${OpenCV_LIBS})
