project(12_sort)
add_library(sort INTERFACE)
target_include_directories(sort INTERFACE include)

# -------------------------TEST--------------------------------

add_executable(shell_sort_test test/shell_sort_test.cc)
target_link_libraries(shell_sort_test PRIVATE sort
                      PRIVATE GTest::Main)


add_executable(quick_sort_test test/quick_sort_test.cc)
target_link_libraries(quick_sort_test PRIVATE sort
                      PRIVATE GTest::Main)

gtest_discover_tests(shell_sort_test)
gtest_discover_tests(quick_sort_test)
