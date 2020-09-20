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

#include "cpic/data/board_data.h"
#include "cpic/solver/brute_force_board_solver.h"
#include "cpic/solver/heuristic_board_solver.h"
#include "cpic/view/board_logger.h"

#include "common/runners.h"

#include <iostream>

using namespace CPic;

using Puzzles::runningTime;

using std::cout;

bool CPic::run() {
  BruteForceBoardSolver bruteSolver;
  HeuristicBoardSolver heuristicSolver;

  BoardSolver *solvers[] = {&bruteSolver, &heuristicSolver};
  auto boards = CPic::createAllBoards();

  for (const auto &data : boards) {
    for (const auto solver : solvers) {
      auto [results, duration] = runningTime([solver, &data] { return solver->solve(&data.board); });

      if (results == data.solution) {
        cout << "CPic: " << solver->name << " solved board " << data.name << ", it took about " << duration
             << " microseconds!\n";
      } else {
        cout << "CPic: " << solver->name << " failed to solve board " << data.name << ", was expecting this:\n";
        CPic::BoardLogger::log(data.solution);
        cout << "CPic: But got this:\n";
        CPic::BoardLogger::log(results);
        return false;
      }
    }
  }

  return true;
}
