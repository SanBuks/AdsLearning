cmake_minimum_required(VERSION 3.20)
project(mca_ds LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          11    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

add_subdirectory(intro)

add_executable(test test.cc)
