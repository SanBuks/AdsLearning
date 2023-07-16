project(test)

add_executable(sort_algorithm_test sort_algorithm_test.cc)
target_link_libraries(sort_algorithm_test PRIVATE tool)
