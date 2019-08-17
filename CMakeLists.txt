#
# Copyright (c) 2018 Emanuel Machado da Silva
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

cmake_minimum_required(VERSION 3.9) # CMP0069
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0069 NEW)

project(Puzzles VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Weverything -pedantic -Wno-c++98-compat -Wno-c++11-extensions -Wno-padded")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic")
endif ()

# Source Files
include_directories(src)
file(GLOB_RECURSE sources src/*.cpp)
list(REMOVE_ITEM sources "${CMAKE_SOURCE_DIR}/src/main.cpp")
add_library(puzzles_lib OBJECT ${sources})

# Executable
add_executable(puzzles "${CMAKE_SOURCE_DIR}/src/main.cpp" $<TARGET_OBJECTS:puzzles_lib>)

include(CheckIPOSupported)
check_ipo_supported(RESULT supportsIPO)
if (supportsIPO)
    set_property(TARGET puzzles PROPERTY INTERPROCEDURAL_OPTIMIZATION true)
endif ()

# Testing
enable_testing()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_subdirectory(libs/googletest)

file(GLOB_RECURSE test_sources tests/*_test.cpp)
foreach (testfile ${test_sources})
    get_filename_component(test_name ${testfile} NAME_WE)
    add_executable(${test_name} ${testfile} $<TARGET_OBJECTS:puzzles_lib>)
    target_link_libraries(${test_name} gtest gtest_main pthread)

    add_test(${test_name} ${test_name})
    add_dependencies(check ${test_name})
endforeach (testfile)

# Workaround for running all tests under one target
add_executable(all_tests ${test_sources} $<TARGET_OBJECTS:puzzles_lib>)
target_link_libraries(all_tests gtest gtest_main pthread)
