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

#include <vector>

using namespace CPic;

using std::vector;

typedef unsigned short ushort;

// Strategies
inline void lookForOneColorLeftColumns(const Board *, BoardState *);
inline void lookForOneColorLeftRows(const Board *, BoardState *);
inline void completeContiguousRows(const Board *, BoardState *);
inline void lookForColorsWhereRowCountAndPossibilityCountAreTheSame(const Board *, BoardState *);

// Tools
inline void paintBlanksOnColumn(BoardState *, ushort column, Color);
inline void paintBlanksOnRow(BoardState *, ushort row, Color);
inline void paintRangeOnRow(BoardState *, Color, ushort row, ushort first, ushort last);

BoardState HeuristicBoardSolver::solve(const Board *board) const {
  BoardState oldResults;
  BoardState newResults = BoardState(board->columnCount, board->rowCount);
  do {
    oldResults = newResults;

    lookForOneColorLeftColumns(board, &newResults);
    lookForOneColorLeftRows(board, &newResults);

    completeContiguousRows(board, &newResults);

    lookForColorsWhereRowCountAndPossibilityCountAreTheSame(board, &newResults);
  } while (oldResults != newResults);

  return oldResults;
}

// Strategies
void lookForOneColorLeftColumns(const Board *board, BoardState *state) {
  for (ushort column = 0; column < board->columnCount; ++column) {
    auto blanks = state->countColorInColumn(column, Blank);

    for (auto color : board->colors) {
      auto total = board->clueForColumn(column, color).amount;
      auto count = state->countColorInColumn(column, color);

      if (total - count == blanks) {
        paintBlanksOnColumn(state, column, color);
        break;
      }
    }
  }
}

void lookForOneColorLeftRows(const Board *board, BoardState *state) {
  for (ushort row = 0; row < board->rowCount; ++row) {
    auto blanks = state->countColorInRow(row, Blank);

    for (auto color : board->colors) {
      auto total = board->clueForRow(row, color).amount;
      auto count = state->countColorInRow(row, color);

      if (total - count == blanks) {
        paintBlanksOnRow(state, row, color);
        break;
      }
    }
  }
}

void completeContiguousRows(const Board *board, BoardState *state) {
  for (ushort row = 0; row < board->rowCount; ++row) {
    for (auto color : board->colors) {
      auto clue = board->clueForRow(row, color);
      if (clue.contiguous == false) continue;

      auto first = state->findFirstInRow(row, color);
      if (first < 0) continue;
      auto last = state->findLastInRow(row, color);

      auto ufirst = static_cast<ushort>(first);
      auto ulast = static_cast<ushort>(last);
      paintRangeOnRow(state, color, row, ufirst, ulast);
    }
  }
}

// TODO: Find a better name, this one is too long
void lookForColorsWhereRowCountAndPossibilityCountAreTheSame(const Board *board, BoardState *state) {
  for (ushort row = 0; row < board->rowCount; ++row) {
    for (auto color : board->colors) {
      auto total = board->clueForRow(row, color).amount;
      if (total == 0) continue;

      auto possibilities = board->countPossibilitiesForRow(row, color);
      if (possibilities == total) {
        for (auto col = 0; col < board->columnCount; ++col) {
          if (board->isPossibility(col, row, color)) {
            state->setColorAt(col, row, color);
          }
        }
      }
    }
  }
}

// Tools
void paintBlanksOnColumn(BoardState *state, ushort column, Color color) {
  auto rowCount = state->rowCount();
  for (ushort row = 0; row < rowCount; ++row) {
    if (state->colorAt(column, row) == Blank) {
      state->setColorAt(column, row, color);
    }
  }
}

void paintBlanksOnRow(BoardState *state, ushort row, Color color) {
  auto columnCount = state->columnCount();
  for (ushort column = 0; column < columnCount; ++column) {
    if (state->colorAt(column, row) == Blank) {
      state->setColorAt(column, row, color);
    }
  }
}

void paintRangeOnRow(BoardState *state, Color color, ushort row, ushort first, ushort last) {
  for (ushort col = first; col <= last; ++col) {
    state->setColorAt(col, row, color);
  }
}
