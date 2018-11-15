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

#include "data/board_data.h"
#include "solver/brute_force_board_solver.h"
#include "solver/heuristic_board_solver.h"
#include "view/board_logger.h"

using std::cout;
using std::endl;

using namespace CPic;

int main() {
  BruteForceBoardSolver bruteSolver;
  HeuristicBoardSolver heuristicSolver;
  BoardLogger logger;

  auto boards = createAllBoards();

  for (auto data: boards) {
    auto bruteCopy = Board(data.board);
    auto bruteResults = bruteSolver.solve(&bruteCopy);
    if (bruteResults == data.solution) {
      cout << "Brute force solved board " << data.name << endl;
    } else {
      cout << "Brute force failed to solve board " << data.name << ", was expecting this: " << endl;
      logger.log(&data.solution);
      cout << "But got this: "<< endl;
      logger.log(&bruteResults);
    }

    auto heuristicCopy = Board(data.board);
    auto heuristicResults = heuristicSolver.solve(&heuristicCopy);
    if (heuristicResults == data.solution) {
      cout << "Heuristics solved board " << data.name << endl;
    } else {
      cout << "Heuristics failed to solve board " << data.name << ", was expecting this: " << endl;
      logger.log(&data.solution);
      cout << "But got this: "<< endl;
      logger.log(&heuristicResults);
    }
  }
}
