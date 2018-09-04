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

#include "heuristic_board_solver.h"

#include <vector>

using namespace CPic;

using std::vector;

typedef unsigned short ushort;

inline void lookForFullColoredColumns(Board*);
inline void paintWholeColumn(Board*, ushort column, ushort color);

void HeuristicBoardSolver::solve(Board* board) const {
  // TODO: Optimize this when we have more heuristics
  vector<vector<int>> oldResults;
  do {
    oldResults = board->results;

    lookForFullColoredColumns(board);
  } while (oldResults != board->results);
}

void lookForFullColoredColumns(Board *board) {
  auto columnCount = static_cast<ushort>(board->columns.size());
  for (ushort column = 0; column < columnCount; ++column) {
    ushort blankCells = board->blankCellsOnColumn(column);
    auto colors = board->missingColorsOnColumn(column);
    for (ushort color = 0; color < colors.size(); ++color) {
      if (colors[color] == blankCells) {
        paintWholeColumn(board, column, color);
      }
    }
  }
}

void paintWholeColumn(Board * board, ushort column, ushort color) {
  auto rowCount = static_cast<ushort>(board->rows.size());
  for (ushort row = 0; row < rowCount; ++row) {
    if (board->results[column][row] == COLOR_BLANK) {
      board->results[column][row] = color;
    }
  }
}
