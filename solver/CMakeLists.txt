cmake_minimum_required(VERSION 3.12)
project(npim
    VERSION 0.0.1
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    # Set up wrapper scripts
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    message("Using ccache")
else()
    message("Cannot find ccache")
endif()

add_subdirectory(cli)
add_subdirectory(np_solver)