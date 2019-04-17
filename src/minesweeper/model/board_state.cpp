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

#include "board_state.h"

#include <algorithm>

using namespace Minesweeper;

using std::vector;

BoardState::BoardState(const Board &board) : board(board), cells(board.cellCount(), 'X') {}

BoardState BoardState::apply(const Move move) const {
  // FIXME: Should handle blanks
  auto index = move.x + (move.y * columnCount());

  auto newCells = this->cells;
  newCells[index] = board.cellAt(index);

  return BoardState(board, newCells);
}

BoardState BoardState::applyAll(const vector<Move> &moves) const {
  // FIXME: Stop doing the new/delete thing
  auto newState = new BoardState(*this);
  for (const auto &move : moves) {
    auto x = newState->apply(move);
    delete newState;
    newState = new BoardState(x);
  }

  auto y = *newState;
  delete newState;

  return y;
}

bool BoardState::isFailed() const {
  auto begin = cells.begin();
  auto end = cells.end();

  return any_of(begin, end, [](auto cell) { return cell == 'B'; });
}

bool BoardState::isSolved() const {
  auto closedCount = 0;

  for (const auto cell : cells) {
    switch (cell) {
    case 'B':
      return false;
    case 'X':
      closedCount++;
    }
  }

  return closedCount == board.bombCount();
}