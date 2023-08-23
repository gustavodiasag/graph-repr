cmake_minimum_required(VERSION 3.16.3)

project(graph-repr C CXX)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(cli_test cli_test.cc)

target_link_libraries(cli_test
    PRIVATE
    GTest::GTest
    source
)

add_test(cli_tests cli_test)