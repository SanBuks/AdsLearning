project(07_bst LANGUAGES CXX)

add_library(bst)
target_sources(bst PUBLIC FILE_SET CXX_MODULES FILES
  bst.cppm
  avl.cppm
)
target_link_libraries(bst PUBLIC bitree)

# -------------------------TEST--------------------------------
add_executable(07_bst_01_bst_search test/01_bst_search.cc)
target_link_libraries(07_bst_01_bst_search PRIVATE bst PRIVATE GTest::Main)

add_executable(07_bst_02_bst_add test/02_bst_add.cc)
target_link_libraries(07_bst_02_bst_add PRIVATE bst PRIVATE GTest::Main)

add_executable(07_bst_03_bst_del test/03_bst_del.cc)
target_link_libraries(07_bst_03_bst_del PRIVATE bst PRIVATE GTest::Main)

add_executable(07_bst_04_avl_add test/04_avl_add.cc)
target_link_libraries(07_bst_04_avl_add PRIVATE bst PRIVATE GTest::Main)

add_executable(07_bst_05_avl_del test/05_avl_del.cc)
target_link_libraries(07_bst_05_avl_del PRIVATE bst PRIVATE GTest::Main)