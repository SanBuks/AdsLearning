cmake_minimum_required(VERSION 3.20)
project(dsa_cpp)
set(MY_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_CXX_STANDARD 11)

include(cmake/import.cmake)
add_subdirectory(02_vector)

set(CMAKE_BUILD_TYPE Debug CACHE INTERNAL "" FORCE)

# install 共有头文件
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include)