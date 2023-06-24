project(05_bintree LANGUAGES CXX)

add_library(bitree INTERFACE)
target_include_directories(bitree INTERFACE include)

# -------------------------TEST--------------------------------
add_executable(insert_remove test/insert_remove.cc)
target_link_libraries(insert_remove PRIVATE bitree PRIVATE GTest::Main)

add_executable(construct test/construct.cc)
target_link_libraries(construct PRIVATE bitree PRIVATE GTest::Main)

add_executable(traverse test/traverse.cc)
target_link_libraries(traverse PRIVATE bitree PRIVATE GTest::Main)