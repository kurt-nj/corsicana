cmake_minimum_required (VERSION 3.1)

project(CorsicanaProject LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

option(CODE_COVERAGE "Enable coverage reporting" OFF)

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
