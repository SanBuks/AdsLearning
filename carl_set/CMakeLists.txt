cmake_minimum_required(VERSION 3.20)
project(carl_set LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          11    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

add_subdirectory(backtrace)
add_subdirectory(dp)
add_subdirectory(linklist)