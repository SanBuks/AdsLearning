cmake_minimum_required(VERSION 3.20)
project(ds_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          20    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

# 导入第三方库
include(cmake/import.cmake)

#add_subdirectory(01_intro)
#add_subdirectory(02_vector)
#add_subdirectory(03_list)
#add_subdirectory(04_stack)
add_subdirectory(05_bitree)
#add_subdirectory(06_graph)
add_subdirectory(07_bst)
#add_subdirectory(12_sort)

#add_custom_target(print COMMAND ${CMAKE_COMMAND} -E echo $<TARGET_FILE:test>)