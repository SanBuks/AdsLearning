cmake_minimum_required(VERSION 3.20)
project(leete_code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE INTERNAL "" FORCE)
endif()

add_subdirectory(math)
add_subdirectory(dp)
add_subdirectory(hash)
add_subdirectory(simulation)

add_executable(test test_main.cpp)

