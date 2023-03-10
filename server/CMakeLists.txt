cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(TimeSyncServer VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR})
include_directories("../common/" "../server_specific/")

file(GLOB time_sync_server_SRC "*.cpp" "../common/*.cpp" "../server_specific/*.cpp")

add_executable(TimeSyncServer ${time_sync_server_SRC})
target_compile_options(TimeSyncServer PRIVATE "-O2" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
set_target_properties(TimeSyncServer PROPERTIES CXX_STANDARD 17)
target_link_libraries(TimeSyncServer -lpthread)

add_executable(TimeSyncServerDebug ${time_sync_server_SRC})
target_compile_options(TimeSyncServerDebug PRIVATE "-g" "-Og" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
set_target_properties(TimeSyncServerDebug PROPERTIES CXX_STANDARD 17)
target_link_libraries(TimeSyncServerDebug -lpthread)

add_executable(TimeSyncServerAsan ${time_sync_server_SRC})
target_compile_options(TimeSyncServerAsan PRIVATE "-fsanitize=address" "-g" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
target_link_options(TimeSyncServerAsan PRIVATE "-fsanitize=address")
set_target_properties(TimeSyncServerAsan PROPERTIES CXX_STANDARD 17)
target_link_libraries(TimeSyncServerAsan -lpthread)

install(TARGETS TimeSyncServer TimeSyncServerDebug TimeSyncServerAsan DESTINATION ${PROJECT_SOURCE_DIR}/../bin)
