project(logn_and_comparator)

add_executable(01_select_sort        01_select_sort.cc)
target_link_libraries(01_select_sort PRIVATE tool)

add_executable(02_bubble_sort        02_bubble_sort.cc)
target_link_libraries(02_bubble_sort PRIVATE tool)

add_executable(03_insert_sort        03_insert_sort.cc)
target_link_libraries(03_insert_sort PRIVATE tool)

add_executable(04_bin_search         04_binary_search.cc)
target_link_libraries(04_bin_search  PRIVATE tool)
