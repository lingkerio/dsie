cmake_minimum_required(VERSION 3.10)
project(bst)

add_library(libbst STATIC bst.cc)

add_executable(bst main.cc bst.cc)
target_link_libraries(bst libbst)
target_compile_features(libbst INTERFACE cxx_std_11)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(RELEASE_MODE)
endif()
