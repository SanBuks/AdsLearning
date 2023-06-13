project(04_bintree LANGUAGES CXX)

add_library(bitree INTERFACE)
target_include_directories(bitree INTERFACE include)
target_link_libraries(bitree INTERFACE vector)
target_link_libraries(bitree INTERFACE queue)
target_link_libraries(bitree INTERFACE stack)

# -------------------------TEST--------------------------------

add_executable(bitree_copy_control_test test/bitree_copy_control_test.cc)
target_link_libraries(bitree_copy_control_test PRIVATE bitree
                                               PRIVATE GTest::Main)

add_executable(bitree_modify_test test/bitree_modify_test.cc)
target_link_libraries(bitree_modify_test PRIVATE bitree
                                         PRIVATE GTest::Main)

add_executable(bitree_traverse_test test/bitree_traverse_test.cc)
target_link_libraries(bitree_traverse_test PRIVATE bitree
                                           PRIVATE GTest::Main)

gtest_discover_tests(bitree_copy_control_test)
gtest_discover_tests(bitree_modify_test)
gtest_discover_tests(bitree_traverse_test)
