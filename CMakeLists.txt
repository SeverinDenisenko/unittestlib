cmake_minimum_required(VERSION 3.10)

project(unittest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

option(ENABLE_TESTING OFF)

add_library(unittest INTERFACE)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(unittest 
    INTERFACE 
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>)

if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
