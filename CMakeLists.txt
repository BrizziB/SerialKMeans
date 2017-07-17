cmake_minimum_required(VERSION 3.6)
project(SerialKMeans)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FileReader.cpp FileReader.h KmeansSolver.cpp KmeansSolver.h Point.h cluster.h FileWriter.h)
add_executable(SerialKMeans ${SOURCE_FILES})