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

#include <iostream>

#include "cpic/data/board_data.h"
#include "cpic/solver/brute_force_board_solver.h"
#include "cpic/solver/heuristic_board_solver.h"
#include "cpic/view/board_logger.h"
#include "minesweeper/data/board_data.h"
#include "minesweeper/model/board_state.h"
#include "minesweeper/solver/brute_force_solver.h"
#include "minesweeper/view/board_logger.h"
#include "sudoku/data/board_data.h"
#include "sudoku/solver/brute_force_board_solver.h"
#include "sudoku/solver/heuristic_board_solver.h"
#include "sudoku/view/board_logger.h"

using std::cout;
using std::endl;

inline bool solveCPic();
inline bool solveMinesweeper();
inline bool solveSudoku();

int main() {
  if (!solveCPic()) return 1;
  if (!solveMinesweeper()) return 1;
  if (!solveSudoku()) return 1;
}

bool solveCPic() {
  CPic::BruteForceBoardSolver bruteSolver;
  CPic::HeuristicBoardSolver heuristicSolver;
  CPic::BoardLogger logger;

  auto boards = CPic::createAllBoards();

  for (auto data : boards) {
    auto bruteResults = bruteSolver.solve(&data.board);
    if (bruteResults == data.solution) {
      cout << "CPic: Brute force solved board " << data.name << endl;
    } else {
      cout << "CPic: Brute force failed to solve board " << data.name << ", was expecting this: " << endl;
      logger.log(&data.solution);
      cout << "CPic: But got this: " << endl;
      logger.log(&bruteResults);
      return false;
    }

    auto heuristicResults = heuristicSolver.solve(&data.board);
    if (heuristicResults == data.solution) {
      cout << "CPic: Heuristics solved board " << data.name << endl;
    } else {
      cout << "CPic: Heuristics failed to solve board " << data.name << ", was expecting this: " << endl;
      logger.log(&data.solution);
      cout << "CPic: But got this: " << endl;
      logger.log(&heuristicResults);
      return false;
    }
  }

  return true;
}

bool solveMinesweeper() {
  Minesweeper::BruteForceSolver bruteSolver;
  Minesweeper::BoardLogger logger;

  auto boards = Minesweeper::createAllBoards();

  for (auto data : boards) {
    auto bruteResults = bruteSolver.solve(&data.board);
    auto state = Minesweeper::BoardState(data.board);
    auto finalBoard = state.applyAll(bruteResults);
    if (finalBoard.isSolved()) {
      cout << "Minesweeper: Brute force solved " << data.name << endl;
    } else {
      cout << "Minesweeper: Brute force failed to solve board " << data.name << " with this layout: " << endl;
      logger.log(data.board);
      cout << endl << "Minesweeper: And got this solution: " << endl;
      logger.log(bruteResults);
      cout << endl << "Minesweeper: Which led to this: " << endl;
      logger.log(finalBoard);
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
      cout << "Sudoku: Brute force solved " << data.name << endl;
    } else {
      cout << "Sudoku: Brute force failed to solve board " << data.name << ", was expecting this: " << endl;
      logger.log(&data.solution);
      cout << "Sudoku: But got this: " << endl;
      logger.log(&bruteResults);
      return false;
    }

    auto heuristicResults = heuristicSolver.solve(&data.board);
    if (heuristicResults == data.solution) {
      cout << "Sudoku: Heuristics solved " << data.name << endl;
    } else {
      cout << "Sudoku: Heuristics failed to solve board " << data.name << ", was expecting this: " << endl;
      logger.log(&data.solution);
      cout << "Sudoku: But got this: " << endl;
      logger.log(&heuristicResults);
      return false;
    }
  }

  return true;
}
