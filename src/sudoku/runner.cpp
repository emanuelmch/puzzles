/*
 * Copyright (c) 2020 Emanuel Machado da Silva
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

#include "runner.h"

#include "sudoku/data/board_data.h"
#include "sudoku/solver/brute_force_board_solver.h"
#include "sudoku/solver/heuristic_board_solver.h"
#include "sudoku/view/board_logger.h"

#include <chrono>
#include <iostream>

using namespace Sudoku;

using std::cout;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;

bool Sudoku::run() {
  BruteForceSolver bruteSolver;
  HeuristicBoardSolver heuristicSolver;

  auto boards = Sudoku::createAllBoards();

  for (const auto &data : boards) {
    auto bruteStart = steady_clock::now();
    auto bruteResults = bruteSolver.solve(&data.board);
    auto bruteEnd = steady_clock::now();

    if (bruteResults == data.solution) {
      auto duration = duration_cast<microseconds>(bruteEnd - bruteStart).count();
      cout << "Sudoku: Brute force solved " << data.name << ", it took about " << duration << " microseconds!\n";
    } else {
      cout << "Sudoku: Brute force failed to solve board " << data.name << ", was expecting this:\n";
      BoardLogger::log(data.solution);
      cout << "Sudoku: But got this:\n";
      BoardLogger::log(bruteResults);
      return false;
    }

    auto heuristicStart = steady_clock::now();
    auto heuristicResults = heuristicSolver.solve(&data.board);
    auto heuristicEnd = steady_clock::now();

    if (heuristicResults == data.solution) {
      auto duration = duration_cast<microseconds>(heuristicEnd - heuristicStart).count();
      cout << "Sudoku: Heuristics solved " << data.name << ", it took about " << duration << " microseconds!\n";
    } else {
      cout << "Sudoku: Heuristics failed to solve board " << data.name << ", was expecting this:\n";
      BoardLogger::log(data.solution);
      cout << "Sudoku: But got this:\n";
      BoardLogger::log(heuristicResults);
      return false;
    }
  }

  return true;
}
