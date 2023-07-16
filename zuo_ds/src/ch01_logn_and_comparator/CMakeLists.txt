project(logn_and_comparator)

add_executable(select_sort 01_select_sort.cc)
target_link_libraries(select_sort PRIVATE tool)

add_executable(bubble_sort 02_bubble_sort.cc)
target_link_libraries(bubble_sort PRIVATE tool)

add_executable(insert_sort 03_insert_sort.cc)
target_link_libraries(insert_sort PRIVATE tool)

add_executable(bin_search 04_binary_search.cc)
target_link_libraries(bin_search PRIVATE tool)
