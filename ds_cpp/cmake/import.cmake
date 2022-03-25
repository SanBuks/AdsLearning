include(FetchContent)

# GTest 单元测试库
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        075810f7a20405ea09a93f68847d6e963212fa62
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest ALIAS gtest)
add_library(GTest::Main  ALIAS gtest_main)

include(GoogleTest)