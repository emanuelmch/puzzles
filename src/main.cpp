/*
 * Copyright (c) 2018 Emanuel Machado da Silva
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

#include "cpic/data/board_data.h"
#include "cpic/solver/brute_force_board_solver.h"
#include "cpic/solver/heuristic_board_solver.h"
#include "cpic/view/board_logger.h"
#include "sudoku/data/board_data.h"
#include "sudoku/solver/brute_force_board_solver.h"
#include "sudoku/solver/heuristic_board_solver.h"
#include "sudoku/view/board_logger.h"

#include <chrono>
#include <iostream>

using std::cout;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

inline bool solveCPic();
inline bool solveSudoku();

int main() {
  auto start = steady_clock::now();
  if (!solveCPic() || !solveSudoku()) return 1;
  auto end = steady_clock::now();
  cout << "All good, we took roughly " << duration_cast<milliseconds>(end - start).count() << " milliseconds!\n";
}

bool solveCPic() {
  CPic::BruteForceBoardSolver bruteSolver;
  CPic::HeuristicBoardSolver heuristicSolver;
  CPic::BoardLogger logger;

  auto boards = CPic::createAllBoards();

  for (auto data : boards) {
    auto bruteResults = bruteSolver.solve(&data.board);
    if (bruteResults == data.solution) {
      cout << "CPic: Brute force solved board " << data.name << "\n";
    } else {
      cout << "CPic: Brute force failed to solve board " << data.name << ", was expecting this:\n";
      logger.log(&data.solution);
      cout << "CPic: But got this:\n";
      logger.log(&bruteResults);
      return false;
    }

    auto heuristicResults = heuristicSolver.solve(&data.board);
    if (heuristicResults == data.solution) {
      cout << "CPic: Heuristics solved board " << data.name << "\n";
    } else {
      cout << "CPic: Heuristics failed to solve board " << data.name << ", was expecting this:\n";
      logger.log(&data.solution);
      cout << "CPic: But got this:\n";
      logger.log(&heuristicResults);
      return false;
    }
  }

  return true;
}

bool solveSudoku() {
  Sudoku::BruteForceSolver bruteSolver;
  Sudoku::HeuristicBoardSolver heuristicSolver;
  Sudoku::BoardLogger logger;

  auto boards = Sudoku::createAllBoards();

  for (auto data : boards) {
    auto bruteResults = bruteSolver.solve(&data.board);
    if (bruteResults == data.solution) {
      cout << "Sudoku: Brute force solved " << data.name << "\n";
    } else {
      cout << "Sudoku: Brute force failed to solve board " << data.name << ", was expecting this:\n";
      logger.log(&data.solution);
      cout << "Sudoku: But got this:\n";
      logger.log(&bruteResults);
      return false;
    }

    auto heuristicResults = heuristicSolver.solve(&data.board);
    if (heuristicResults == data.solution) {
      cout << "Sudoku: Heuristics solved " << data.name << "\n";
    } else {
      cout << "Sudoku: Heuristics failed to solve board " << data.name << ", was expecting this:\n";
      logger.log(&data.solution);
      cout << "Sudoku: But got this:\n";
      logger.log(&heuristicResults);
      return false;
    }
  }

  return true;
}
