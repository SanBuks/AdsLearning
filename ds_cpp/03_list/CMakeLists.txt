project(02_list LANGUAGES CXX)

add_library(list INTERFACE)
target_include_directories(list INTERFACE include)

# -------------------------TEST--------------------------------

add_executable(list_test test/list_test.cc)
target_link_libraries(list_test PRIVATE list
                                     PRIVATE GTest::Main)

gtest_discover_tests(list_test)
