project(intro)

set(CMAKE_CXX_STANDARD 14)

add_executable(01_select_sort   src/01_select_sort.cc)
add_executable(02_bubble_sort   src/02_bubble_sort.cc)
add_executable(03_insert_sort   src/03_insert_sort.cc)
add_executable(04_random_array  src/04_random_array.cc)
add_executable(0162 0162_find_peak_element.cc) # 简单题(二分/局部最小)

add_executable(05_binary_search src/05_binary_search.cc)
add_executable(0136 0136_single_number.cc)     # 简单题(异或)
add_executable(0137 0137_single_number_ii.cc)  # 中等题(异或)
add_executable(0260 0260_single_number_iii.cc) # 简单题(异或)




#0852. Peak Index in a Mountain Array
#1901. Find a Peak Element II
#2137. Pour Water Between Buckets to Make Water Levels Equal
#2210. Count Hills and Valleys in an Array