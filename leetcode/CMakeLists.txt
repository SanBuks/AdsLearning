cmake_minimum_required(VERSION 3.20)
project(leete_code LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          11    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

# 格式
# add_executable(xxxx xxxx_yyyyyyyyy.cc) 简单题(数组 遍历)

#add_subdirectory(array)
#add_subdirectory(bits)
add_subdirectory(dp)
#add_subdirectory(greedy)
#add_subdirectory(hash)
#add_subdirectory(linklist)
#add_subdirectory(math)
#add_subdirectory(search)
#add_subdirectory(simulation)
#add_subdirectory(slide_window)
#add_subdirectory(stack)
#add_subdirectory(string)
#add_subdirectory(tree)
#add_subdirectory(two_pointer)

add_executable(test test_main.cc)
add_executable(individual_value_calc individual_value_calc.cc)

# PRIVATE -fno-elide-constructors
#add_executable(complex  complex.cc)
#add_executable(m_string m_string.cc)
#add_executable(image    image.cc)

