cmake_minimum_required(VERSION 3.0)

project(advection_serial)

add_executable(adv_serial advection_implicit_serial.c)
target_link_libraries(adv_serial m)

add_library(advection_implicit_serial SHARED advection_implicit_serial.c)
