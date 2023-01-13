cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(TimeSyncClient VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR})
include_directories("../common/" "../client_specific/")

file(GLOB time_sync_client_SRC "*.cpp" "../common/*.cpp" "../client_specific/*.cpp")

add_executable(TimeSyncClient ${time_sync_client_SRC})
target_compile_options(TimeSyncClient PRIVATE "-O2" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
set_target_properties(TimeSyncClient PROPERTIES CXX_STANDARD 17)
target_link_libraries(TimeSyncClient -lpthread)

add_executable(TimeSyncClientDebug ${time_sync_client_SRC})
target_compile_options(TimeSyncClientDebug PRIVATE "-g" "-Og" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
set_target_properties(TimeSyncClientDebug PROPERTIES CXX_STANDARD 17)
target_link_libraries(TimeSyncClientDebug -lpthread)

add_executable(TimeSyncClientAsan ${time_sync_client_SRC})
target_compile_options(TimeSyncClientAsan PRIVATE "-fsanitize=address" "-g" "-Wall" "-Wpedantic" "-Werror" "-Wextra")
target_link_options(TimeSyncClientAsan PRIVATE "-fsanitize=address")
set_target_properties(TimeSyncClientAsan PROPERTIES CXX_STANDARD 17)
target_link_libraries(TimeSyncClientAsan -lpthread)

install(TARGETS TimeSyncClient TimeSyncClientDebug TimeSyncClientAsan DESTINATION ${PROJECT_SOURCE_DIR}/../bin)
