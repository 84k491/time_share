cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)

project(TimeSyncServer VERSION 1.0)

include_directories(${PROJECT_SOURCE_DIR})
include_directories("../common/")

file(GLOB time_sync_server_SRC "*.cpp" "../common/*.cpp")
add_executable(TimeSyncServer ${time_sync_server_SRC})

target_compile_options(TimeSyncServer PRIVATE "-g" "-Og" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
set_target_properties(TimeSyncServer PROPERTIES CXX_STANDARD 17)

target_link_libraries(TimeSyncServer -lpthread)
