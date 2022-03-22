project(02_vector LANGUAGES CXX)

add_library(vector INTERFACE)
target_include_directories(vector INTERFACE include)
target_link_libraries(vector INTERFACE fib)

# -------------------------TEST--------------------------------

add_executable(vector_copy_control_test test/vector_copy_control_test.cc)
target_link_libraries(vector_copy_control_test PRIVATE vector
                                               PRIVATE GTest::Main)

add_executable(vector_modify_test test/vector_modify_test.cc)
target_link_libraries(vector_modify_test PRIVATE vector
                                         PRIVATE GTest::Main)

add_executable(vector_access_test test/vector_access_test.cc)
target_link_libraries(vector_access_test PRIVATE vector
                                         PRIVATE GTest::Main)
# 将 fib 拷贝到测试目录下
add_custom_command(TARGET vector_access_test POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:fib> $<TARGET_FILE_DIR:vector_access_test>)

add_executable(vector_sort_test test/vector_sort_test.cc)
target_link_libraries(vector_sort_test PRIVATE vector
                                       PRIVATE GTest::Main)

gtest_discover_tests(vector_copy_control_test)
gtest_discover_tests(vector_modify_test)
gtest_discover_tests(vector_access_test)
gtest_discover_tests(vector_sort_test)
