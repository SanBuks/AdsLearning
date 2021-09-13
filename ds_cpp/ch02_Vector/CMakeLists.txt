#cmake -G"MinGW Makefiles"
#      -DCMAKE_C_COMPILER=gcc
#      -DCMAKE_CXX_COMPILER=g++
#      -DCMAKE_MAKE_PROGRAM=make ..

cmake_minimum_required(VERSION 3.20)
project(ch02_Vector)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(ch02_Vector vector_test.cc vector.cc vector.h)