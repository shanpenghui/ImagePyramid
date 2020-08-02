cmake_minimum_required(VERSION 3.14)
project(image_pyramid)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 3.0 QUIET)


include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(image_pyramid main.cpp)
target_link_libraries(image_pyramid ${OpenCV_LIBS})
