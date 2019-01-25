cmake_minimum_required (VERSION 3.1)

project(CorsicanaProject)

set (CMAKE_CXX_STANDARD 11)

##############################################
# Corsicana Library
# Header only so no build
##############################################
add_library(corsicana INTERFACE)
target_include_directories(corsicana INTERFACE include/)

##############################################
# Test Builds
##############################################
enable_testing()
add_subdirectory(test)
