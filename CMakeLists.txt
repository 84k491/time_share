cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(TimeSyncSystem VERSION 1.0)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(tests)
