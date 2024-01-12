project(test)

add_executable(sort_algorithm_test        sort_test.cc)
target_link_libraries(sort_algorithm_test PRIVATE tool)

add_executable(random_test                random_test.cc)
target_link_libraries(random_test         PRIVATE tool)