project(02_list LANGUAGES CXX)

add_library(list INTERFACE)
target_include_directories(list INTERFACE include)

# -------------------------TEST--------------------------------

add_executable(list_copy_control_test test/list_copy_control_test.cc)
target_link_libraries(list_copy_control_test PRIVATE list
                                             PRIVATE GTest::Main)

add_executable(list_access_test test/list_access_test.cc)
target_link_libraries(list_access_test PRIVATE list
                                       PRIVATE GTest::Main)

add_executable(list_modify_test test/list_modify_test.cc)
target_link_libraries(list_modify_test PRIVATE list
                                       PRIVATE GTest::Main)

add_executable(list_sort_test test/list_sort_test.cc)
target_link_libraries(list_sort_test PRIVATE list
                                     PRIVATE GTest::Main)

gtest_discover_tests(list_copy_control_test)
gtest_discover_tests(list_access_test)
gtest_discover_tests(list_modify_test)
gtest_discover_tests(list_sort_test)

