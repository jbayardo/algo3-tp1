cmake_minimum_required(VERSION 2.8)
project(algo3_tp1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2")

set(SOURCE_FILES src/main.cpp)
add_executable(algo3_tp1 ${SOURCE_FILES} src/Median.cpp src/Median.h src/Path.cpp src/Path.h src/Explorers.cpp src/Explorers.h src/Statistics.cpp src/Statistics.h)