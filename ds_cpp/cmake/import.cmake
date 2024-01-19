include(FetchContent)

#------------------- GTest 单元测试-------------------#
if (EXISTS ${CMAKE_SOURCE_DIR}/thirdparty/googletest)
  set(repo_googletest "file://${CMAKE_SOURCE_DIR}/thirdparty/googletest")
else ()
  set(repo_googletest "git@github.com:google/googletest.git")
endif ()

set(FETCHCONTENT_SOURCE_DIR_googletest "${CMAKE_SOURCE_DIR}/thirdparty/gtest")
FetchContent_Declare(
  googletest
  GIT_REPOSITORY ${repo_googletest}
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest ALIAS gtest)
add_library(GTest::Main  ALIAS gtest_main)
include(GoogleTest)
