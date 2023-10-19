cmake_minimum_required(VERSION 3.13.4)
project(FixedPoint)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_library(Fixed-Point SHARED
    # List your source files here.
    FixedPoint.cpp
)
