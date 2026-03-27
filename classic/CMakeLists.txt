cmake_minimum_required(VERSION 3.14)
project(classic VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(test_graph test_graph.cpp)
target_include_directories(test_graph PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_graph PRIVATE GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(test_graph)
