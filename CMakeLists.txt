cmake_minimum_required(VERSION 3.5)

project(ocrCaptchaMnn)

set(CMAKE_CXX_STANDARD 14)

# Enable static linking for MNN
set(MNN_BUILD_SHARED_LIBS OFF CACHE BOOL "Build MNN as static library" FORCE)
set(MNN_ENABLE_NEON OFF CACHE BOOL "Enable NEON optimization" FORCE)

# Enable static linking for OpenCV
set(OpenCV_STATIC ON CACHE BOOL "Static link OpenCV" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libs" FORCE)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})

add_subdirectory(MNN)

include_directories(MNN/include)
add_executable(ocrCaptchaMnn main.cpp OcrCaptcha.hpp words.h)

target_link_libraries(ocrCaptchaMnn PUBLIC MNN ${OpenCV_LIBS})

# Enable testing
enable_testing()

# Add test
add_test(
    NAME OcrCaptchaTest
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/ocrCaptchaMnn 
            ${CMAKE_CURRENT_SOURCE_DIR}/ocr.captcha.sim.mnn 
            ${CMAKE_CURRENT_SOURCE_DIR}/captcha.png
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

