cmake_minimum_required (VERSION 3.1)

project(ACProj)

set (CMAKE_CXX_STANDARD 11)

add_library(corsicana INTERFACE)
target_include_directories(corsicana INTERFACE include/)

enable_testing()
add_subdirectory(test)
