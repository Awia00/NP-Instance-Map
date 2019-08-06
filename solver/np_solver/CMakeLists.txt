cmake_minimum_required(VERSION 3.10)
SET(SOLUTION_NAME "npim")
SET(MODULE_NAME "npim-np-solver")
SET(TEST_NAME "npim-np-solver-tests")
SET(MODULE_NAME_CONFIG "npim-np-solver-config")
message(STATUS "Project: " ${MODULE_NAME})

project(${MODULE_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX)

include(GNUInstallDirs)

add_library(${MODULE_NAME} INTERFACE)

target_include_directories(${MODULE_NAME} 
    INTERFACE 
    include/)


# test executable
file(GLOB_RECURSE TESTS "tests/*.cpp")
add_executable(${TEST_NAME} ${TESTS})
target_link_libraries(${TEST_NAME} ${MODULE_NAME} doctest)


install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${SOLUTION_NAME})