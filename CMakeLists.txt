cmake_minimum_required(VERSION 3.15)
project(MeanShiftClustering)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(MeanShiftClustering C++/main.cpp C++/Utils.h C++/Point.cpp C++/Point.h C++/MeanShift.cpp C++/MeanShift.h C++/Cluster.cpp C++/Cluster.h C++/ClusterManager.cpp C++/ClusterManager.h C++/Utils.cpp C++/SpeedupTests.h C++/SpeedUpTests.cpp)

target_link_libraries(MeanShiftClustering -lstdc++fs)