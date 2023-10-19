cmake_minimum_required(VERSION 3.13.4)
project(UnitTest)

#===============================================================================
# 3. ADD THE TARGET
#===============================================================================
enable_testing()

add_executable(UnitTest
    # List your source files here.
    UnitTest.cpp
)


# Allow undefined symbols in shared objects on Darwin (this is the default
# behaviour on Linux)
target_link_libraries(UnitTest
  "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>")
  target_link_libraries(
  UnitTest
  gtest_main
)
include(GoogleTest)
gtest_discover_tests(UnitTest)
