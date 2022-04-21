cmake_minimum_required(VERSION 3.0)

project(cexamplelib)

add_library(c_example1_lib SHARED example1.c)
add_library(c_example2_lib SHARED example2.c)
add_library(c_example3_lib SHARED example3.c)
add_library(c_example4_lib SHARED example4.c)

add_library(final SHARED example1.c example2.c example3.c example4.c mandelbrot.c)

add_library(julia SHARED julia.c)
