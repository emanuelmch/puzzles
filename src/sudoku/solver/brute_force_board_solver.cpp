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

#include "brute_force_board_solver.h"

#include <cassert>
#include <stack>
#include <vector>

using namespace Sudoku;

using std::stack;
using std::vector;

typedef unsigned short ushort;

const vector<Board> getNext(const Board *board) {
  vector<Board> next;

  auto nextCell = board->firstEmptyCell();
  assert(nextCell < 81);

  for (ushort i = 1; i <= 9; ++i) {
    Board copy(*board);
    copy.setCell(nextCell, i);
    next.emplace_back(copy);
  }

  return next;
}

const Board BruteForceSolver::solve(const Board *board) const {
  stack<Board> nodes;
  nodes.push(*board);

  do {
    auto top = nodes.top();
    auto isValid = top.isValid();
    if (isValid && top.isFull()) {
      return top;
    } else {
      nodes.pop();

      if (isValid) {
        for (const auto &node : getNext(&top)) {
          nodes.push(node);
        }
      }
    }
  } while (!nodes.empty());

  // Couldn't find anything!
  return *board;
}
