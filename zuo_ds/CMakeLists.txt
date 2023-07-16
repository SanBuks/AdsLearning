cmake_minimum_required(VERSION 3.20)
project(zuo_ds LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          17    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

add_subdirectory(test)
add_subdirectory(src/ch01_logn_and_comparator)
add_subdirectory(leetcode)

add_library(tool INTERFACE)
target_include_directories(tool INTERFACE tool)

add_executable(test test.cc)
target_link_libraries(test PRIVATE tool)
