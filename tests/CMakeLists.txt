cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)

project(Tests VERSION 1.0)

include_directories(${PROJECT_SOURCE_DIR})
include_directories("../common/")

file(GLOB tests_SRC "*.cpp" "../common/*.cpp")
add_executable(Tests ${tests_SRC})

target_compile_options(Tests PRIVATE "-g" "-Og" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
set_target_properties(Tests PROPERTIES CXX_STANDARD 17)

enable_testing()

target_link_libraries(
  Tests
  -lpthread
  -lgtest
  -lgtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)