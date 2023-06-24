project(07_bst LANGUAGES CXX)

add_library(bst INTERFACE)
target_include_directories(bst INTERFACE include)
target_link_libraries(bst INTERFACE bitree)
#target_link_libraries(bitree INTERFACE vector)
#target_link_libraries(bitree INTERFACE queue)
#target_link_libraries(bitree INTERFACE stack)


# -------------------------TEST--------------------------------
add_executable(insert test/insert.cc)
target_link_libraries(insert PRIVATE bst PRIVATE GTest::Main)