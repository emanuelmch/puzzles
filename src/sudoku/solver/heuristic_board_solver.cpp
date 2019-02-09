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

#include "heuristic_board_solver.h"

#include <cassert>
#include <list>

using namespace Sudoku;

typedef unsigned short ushort;

inline void findRowWithOneBlank(Board *, ushort row);

const Board HeuristicBoardSolver::solve(const Sudoku::Board *board) const {
  Board oldBoard = *board;
  Board newBoard = *board;

  do {
    oldBoard = newBoard;

    for (auto i = 0; i < 9; ++i) {
      findRowWithOneBlank(&newBoard, i);
    }
  } while (oldBoard != newBoard);

  return newBoard;
}

void findRowWithOneBlank(Board *board, ushort row) {
  auto blankCell = -1;
  std::list<ushort> missingValues = {1, 2, 3, 4, 5, 6, 7, 8, 9};


  for (ushort i = 0; i < 9; ++i) {
    auto cell = board->getCell(9 * row + i);
    if (cell == 0) {
      if (blankCell == -1) {
        blankCell = i;
      } else {
        return;
      }
    } else {
      missingValues.remove(cell);
    }
  }

  if (blankCell != -1) {
    assert(missingValues.size() == 1);

    board->setCell(9 * row + blankCell, missingValues.front());
  }
}
