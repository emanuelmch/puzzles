/*
 * Copyright (c) 2019 Emanuel Machado da Silva
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include "cpic/solver/brute_force_board_solver.h"
#include "cpic/solver/heuristic_board_solver.h"

using namespace CPic;

// First, the factory functions
template <class T>
BoardSolver *CreateBoardSolver();

template <>
BoardSolver *CreateBoardSolver<BruteForceBoardSolver>() {
  return new BruteForceBoardSolver;
}

template <>
BoardSolver *CreateBoardSolver<HeuristicBoardSolver>() {
  return new HeuristicBoardSolver;
}

// Now, the Test template
template <typename T>
class BoardSolverTest : public ::testing::Test {
public:
  BoardSolverTest() : solver(CreateBoardSolver<T>()) {}

  ~BoardSolverTest() override { delete solver; }

  BoardSolver *solver;
};

// And last, create the Typed Test Case
using BoardSolverTypes = ::testing::Types<BruteForceBoardSolver, HeuristicBoardSolver>;
TYPED_TEST_SUITE(BoardSolverTest, BoardSolverTypes, );
