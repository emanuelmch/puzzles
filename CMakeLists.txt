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
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -Werror -Wall -Wextra -Wno-missing-braces")

# Pre-requisites
try_compile(supportsSetContains ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/check_set_contains.cpp)
if (supportsSetContains)
    message(STATUS "Compiler supports std::set::contains")
    add_compile_definitions(HAS_STD_SET_CONTAINS)
else ()
    message(STATUS "Compiler does NOT support std::set::contains")
endif ()

# Source Files
include_directories(src)
add_library(puzzles_lib OBJECT
        src/cpic/runner.cpp
        src/cpic/data/easy.cpp
        src/cpic/data/trivial.cpp
        src/cpic/model/board.cpp
        src/cpic/model/board_builder.cpp
        src/cpic/model/board_state.cpp
        src/cpic/solver/brute_force_board_solver.cpp
        src/cpic/solver/heuristic_board_solver.cpp
        src/cpic/view/board_logger.cpp
        src/maths/expressions.cpp
        src/maths/runner.cpp
        src/shurikens/logger.cpp
        src/shurikens/model.cpp
        src/shurikens/runner.cpp
        src/shurikens/data/easy.cpp
        src/shurikens/data/real.cpp
        src/shurikens/data/trivial.cpp
        src/shurikens/solver/breadth_search_solver.cpp
        src/shurikens/solver/depth_search_solver.cpp
        src/sudoku/runner.cpp
        src/sudoku/data/easy.cpp
        src/sudoku/data/trivial.cpp
        src/sudoku/model/board.cpp
        src/sudoku/solver/brute_force_board_solver.cpp
        src/sudoku/solver/heuristic_board_solver.cpp
        src/sudoku/view/board_logger.cpp
        )

# Executable
add_executable(puzzles src/main.cpp $<TARGET_OBJECTS:puzzles_lib>)
add_custom_target(run "./puzzles" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(run puzzles)

include(CheckIPOSupported)
check_ipo_supported(RESULT supportsIPO)
if (supportsIPO)
    set_property(TARGET puzzles PROPERTY INTERPROCEDURAL_OPTIMIZATION true)
endif ()

# Testing
enable_testing()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_subdirectory(libs/googletest)

set(test_sources
        tests/common/arbitrary_container_test.cpp
        tests/common/numbers_test.cpp
        tests/cpic/model/cpic_board_builder_test.cpp
        tests/cpic/model/cpic_board_solver_test.cpp
        tests/cpic/model/cpic_board_state_test.cpp
        tests/cpic/model/cpic_board_test.cpp
        tests/maths/maths_expressions_test.cpp
        tests/maths/maths_primes_test.cpp
        tests/shurikens/shurikens_model_test.cpp
        tests/sudoku/model/sudoku_board_test.cpp
        tests/sudoku/model/sudoku_board_validity_test.cpp
        )

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
