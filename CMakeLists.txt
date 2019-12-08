cmake_minimum_required(VERSION 3.15)
project(metaprog)

set(CMAKE_CXX_STANDARD 11)

add_executable(readCSV hw1/readCSV.cpp)
add_executable(indexOf hw2/indexOf.cpp)
add_executable(scatter hw3/scatter.cpp)
add_executable(functor hw4/main.cpp hw4/args.h)
