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

inline void lookForOneColorLeftColumns(Board*);
inline ushort clueForColumn(const Board*, ushort column, ushort colorPosition);
inline void paintBlanksOnColumn(Board*, ushort column, Color color);

void HeuristicBoardSolver::solve(Board* board) const {
  // TODO: Optimize this when we have more heuristics
  vector<vector<Color>> oldResults;
  do {
    oldResults = board->results;

    lookForOneColorLeftColumns(board);
  } while (oldResults != board->results);
}

void lookForOneColorLeftColumns(Board *board) {
  auto columnCount = static_cast<ushort>(board->columns.size());
  for (ushort column = 0; column < columnCount; ++column) {
    auto blanks = board->countColorInColumn(column, Blank);
    ushort count0 = clueForColumn(board, column, 0);
    ushort count1 = clueForColumn(board, column, 1);

    if (count0 == blanks) {
      paintBlanksOnColumn(board, column, C0);
    } else if (count1 == blanks) {
      paintBlanksOnColumn(board, column, C1);
    }
  }
}

//FIXME: We should have a Color, not a colorPosition
inline ushort clueForColumn(const Board* board, ushort column, ushort colorPosition) {
  return board->columns[column][colorPosition];
}

void paintBlanksOnColumn(Board *board, ushort column, Color color) {
  auto rowCount = static_cast<ushort>(board->rows.size());
  for (ushort row = 0; row < rowCount; ++row) {
    if (board->results[column][row] == Blank) {
      board->results[column][row] = color;
    }
  }
}
