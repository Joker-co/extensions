cmake_minimum_required(VERSION 3.12.0)

project(nms)

add_compile_options(-std=c++11)

set(SRC_LIST nms.cpp)
add_executable(nms ${SRC_LIST})