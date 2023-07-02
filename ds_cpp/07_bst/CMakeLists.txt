project(07_bst LANGUAGES CXX)

add_library(bst INTERFACE)
target_include_directories(bst INTERFACE include)
target_link_libraries(bst INTERFACE bitree)
#target_link_libraries(bitree INTERFACE vector)
#target_link_libraries(bitree INTERFACE queue)
#target_link_libraries(bitree INTERFACE stack)


# -------------------------TEST--------------------------------
add_executable(add test/add.cc)
target_link_libraries(add PRIVATE bst PRIVATE GTest::Main)

add_executable(search test/search.cc)
target_link_libraries(search PRIVATE bst PRIVATE GTest::Main)

add_executable(remove test/remove.cc)
target_link_libraries(remove PRIVATE bst PRIVATE GTest::Main)
