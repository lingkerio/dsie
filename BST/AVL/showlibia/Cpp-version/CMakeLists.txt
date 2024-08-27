cmake_minimum_required(VERSION 3.10)
project(avl)

add_library(libavl STATIC avl.cc)

add_executable(avl main.cc avl.cc)
target_link_libraries(avl libavl)
target_compile_features(libavl INTERFACE cxx_std_17)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE)
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
    message(STATUS "CMAKE_BUILD_TYPE = Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(RELEASE_MODE)
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
    message(STATUS "CMAKE_BUILD_TYPE = Release")
endif()
