cmake_minimum_required(VERSION 3.15)
project(midterm_parallel_computing)

set(CMAKE_CXX_STANDARD 14)

add_executable(midterm_parallel_computing main.cpp Utils.h Point.cpp Point.h MeanShift.cpp)