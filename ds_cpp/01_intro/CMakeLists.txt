project(01_intro LANGUAGES CXX)

add_library(intro INTERFACE)
target_include_directories(intro INTERFACE include)

add_library(fib SHARED src/fib.cc)
target_include_directories(fib PUBLIC include)

# -------------------------TEST--------------------------------

add_executable(bubble_sort_test test/bubble_sort_test.cc)
target_link_libraries(bubble_sort_test PRIVATE intro
                                       PRIVATE GTest::Main)

add_executable(count_ones_test test/count_ones_test.cc)
target_link_libraries(count_ones_test PRIVATE intro
                                      PRIVATE GTest::Main)

add_executable(power2_test test/power2_test.cc)
target_link_libraries(power2_test PRIVATE intro
                                  PRIVATE GTest::Main)

add_executable(ordinary_element_test test/ordinary_element_test.cc)
target_link_libraries(ordinary_element_test PRIVATE intro
                                            PRIVATE GTest::Main)

add_executable(fib_test test/fib_test.cc)
target_link_libraries(fib_test PRIVATE fib
                               PRIVATE GTest::Main)

add_executable(shift_test test/shift_test.cc)
target_link_libraries(shift_test PRIVATE intro
                                 PRIVATE GTest::Main)

add_executable(gcd_test test/gcd_test.cc)
target_link_libraries(gcd_test PRIVATE intro
                               PRIVATE GTest::Main)

add_executable(subset_test test/subset_test.cc)
target_link_libraries(subset_test PRIVATE intro
                                  PRIVATE GTest::Main)

add_executable(hanoi_test test/hanoi_test.cc)
target_link_libraries(hanoi_test PRIVATE intro
                                 PRIVATE GTest::Main)

gtest_discover_tests(bubble_sort_test)
gtest_discover_tests(count_ones_test)
gtest_discover_tests(power2_test)
gtest_discover_tests(ordinary_element_test)
gtest_discover_tests(fib_test)
gtest_discover_tests(gcd_test)
gtest_discover_tests(subset_test)
gtest_discover_tests(hanoi_test)