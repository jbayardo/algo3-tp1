cmake_minimum_required(VERSION 3.2)
project(algo3_tp1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(algo3_tp1 ${SOURCE_FILES} src/Median.cpp src/Median.h src/Camino.cpp src/Camino.h src/Exploradoras.cpp src/Exploradoras.h)