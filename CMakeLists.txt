cmake_minimum_required(VERSION 3.5)
project(callff)

option(BUILD_TESTS "Build Tests" NO)
option(BUILD_M32 "Build for x86 machines" NO)

set (CMAKE_CXX_STANDARD 11)

include_directories(SYSTEM PUBLIC ./include)

add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
