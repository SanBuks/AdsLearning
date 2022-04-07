project(04_stack LANGUAGES CXX)

add_library(stack INTERFACE)
target_include_directories(stack INTERFACE include)
target_link_libraries(stack INTERFACE vector)

add_library(queue INTERFACE)
target_include_directories(queue INTERFACE include)
target_link_libraries(queue INTERFACE list)

# -------------------------TEST--------------------------------

add_executable(stack_test test/stack_test.cc)
target_link_libraries(stack_test PRIVATE stack
                                 PRIVATE GTest::Main)

add_executable(queue_test test/queue_test.cc)
target_link_libraries(queue_test PRIVATE queue
                                 PRIVATE GTest::Main)

add_executable(rpn_test test/rpn_test.cc)
target_link_libraries(rpn_test PRIVATE stack
                               PRIVATE GTest::Main)

gtest_discover_tests(stack_test)
gtest_discover_tests(queue_test)
gtest_discover_tests(rpn_test)