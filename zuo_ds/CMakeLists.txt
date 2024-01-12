cmake_minimum_required(VERSION 3.25)
project(zuo_ds LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          20    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

add_subdirectory(ch01_logn_and_comparator)

add_subdirectory(leetcode)

add_subdirectory(tool)
add_subdirectory(test)

