cmake_minimum_required (VERSION 3.1)

project(CorsicanaProject LANGUAGES CXX)
include(CTest)

##############################################
# Set C++ standard
# Use c++11 if not set by the user
##############################################
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
option(BUILD_BENCHMARK "Enable benchmark building" ON)

##############################################
# Corsicana Library
# Header only so no build
##############################################
add_library(corsicana INTERFACE)
target_include_directories(corsicana INTERFACE include/)

##############################################
# Test Builds
##############################################
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif(BUILD_TESTING)

##############################################
# Benchmark Builds
##############################################
if(BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif(BUILD_BENCHMARK)

###########################################################
# Install target
###########################################################

install(DIRECTORY include/ DESTINATION include/)