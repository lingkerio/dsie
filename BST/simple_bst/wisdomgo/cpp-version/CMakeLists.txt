cmake_minimum_required(VERSION 3.22.1)
project(wisdomgo)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(wisdomgo src/main.cpp src/bst.cpp)