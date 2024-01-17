project(05_bintree LANGUAGES CXX)

add_library(bitree)
target_sources(bitree PUBLIC FILE_SET CXX_MODULES FILES
  bitree.cppm
  binode.cppm
  common.cppm
)

# -------------------------TEST--------------------------------
add_executable(05_bitree_01_construct test/01_construct.cc)
target_link_libraries(05_bitree_01_construct PRIVATE bitree GTest::Main)

add_executable(05_bitree_02_edit test/02_edit.cc)
target_link_libraries(05_bitree_02_edit PRIVATE bitree PRIVATE GTest::Main)

add_executable(05_bitree_03_traverse test/03_traverse.cc)
target_link_libraries(05_bitree_03_traverse PRIVATE bitree PRIVATE GTest::Main)

add_executable(05_bitree_04_zigzag test/04_zigzag.cc)
target_link_libraries(05_bitree_04_zigzag PRIVATE bitree PRIVATE GTest::Main)
