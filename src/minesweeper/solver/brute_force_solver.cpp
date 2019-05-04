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

#include "brute_force_solver.h"

#include "minesweeper/model/board_state.h"

#include <cassert>

using namespace Minesweeper;

using std::vector;

const vector<Minesweeper::Point2D> BruteForceSolver::solve(const Minesweeper::Board *board) const {
  vector<Point2D> moves = {board->firstMove};

  BoardState initialState(*board);
  initialState.apply(board->firstMove);
  assert(initialState.isFailed() == false);

  for (auto x = 0; x < board->columnCount(); ++x) {
    for (auto y = 0; y < board->rowCount(); ++y) {
      Point2D move(x, y);
      if (move == board->firstMove) continue;

      auto tempState = initialState.apply(move);
      if (tempState.isFailed() == false) {
        moves.push_back(move);
      }
    }
  }

  return moves;
}
