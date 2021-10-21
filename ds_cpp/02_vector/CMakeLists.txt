project(02_vector)

# build
add_library(vector INTERFACE)
add_library(dsa_cpp::vector ALIAS vector)
target_include_directories(vector INTERFACE include/)

# test
add_executable(vector_test tests/vector_test.cc)
target_link_libraries(vector_test
                      PRIVATE dsa_cpp::vector
                      PRIVATE GTest::GTest
                      PRIVATE GTest::Main)
enable_testing()
add_test(test_all vector_test)

# install vector.h
install(DIRECTORY ${02_vector_SOURCE_DIR}/include/
        DESTINATION include)
