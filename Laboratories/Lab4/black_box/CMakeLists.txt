cmake_minimum_required(VERSION 3.0)

project(black-box)

add_executable(black-box main.cpp)
set_target_properties(black-box PROPERTIES CXX_STANDARD 20)
