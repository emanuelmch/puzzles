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

#pragma once

#include "board.h"

namespace Minesweeper {

class BoardState {
public:
  BoardState(const BoardState &o) = default;
  explicit BoardState(const Board &board);

  ushort cellCount() const { return cells.size(); }
  ushort columnCount() const { return board.columnCount(); }

  char cellAt(ushort index) const { return cells.at(index); }

  bool isFailed() const;
  bool isSolved() const;

  BoardState apply(const Move) const;
  BoardState applyAll(const std::vector<Move> &moves) const;

private:
  const Board board;
  const std::vector<char> cells;

  BoardState(const Board &board, std::vector<char> cells) : board(board), cells(cells) {}
};
}
