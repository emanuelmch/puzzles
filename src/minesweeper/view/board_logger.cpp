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

#include "board_logger.h"

#include <algorithm>
#include <iostream>

using namespace Minesweeper;

using std::cout;
using std::endl;
using std::for_each;

void BoardLogger::log(const Board &board) const {
  auto cellCount = board.cellCount();
  auto columns = board.columnCount();

  for (auto i = 0; i < cellCount; ++i) {
    cout << board.cellAt(i) << " ";
    if ((i + 1) % columns == 0) {
      cout << endl;
    }
  }
}

void BoardLogger::log(const BoardState &state) const {
  auto cellCount = state.cellCount();
  auto columns = state.columnCount();

  for (auto i = 0; i < cellCount; ++i) {
    cout << state.cellAt(i) << " ";
    if ((i + 1) % columns == 0) {
      cout << endl;
    }
  }
}

void BoardLogger::log(const std::vector<Move> &moves) const {
  auto begin = moves.begin();
  auto end = moves.end();
  for_each(begin, end, [](auto it) { cout << it << " "; });
}
