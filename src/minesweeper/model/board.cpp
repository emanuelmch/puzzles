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

#include "board.h"

#include "common/numbers.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace Minesweeper;
using Puzzles::Numbers::fitsUShort;

using std::count_if;
using std::initializer_list;
using std::to_string;
using std::vector;

std::ostream &Minesweeper::operator<<(std::ostream &os, const Point2D &move) {
  return os << "(" << move.x << "," << move.y << ") ";
}

inline ushort countBombsAround(const vector<bool> &bombs, ushort rows, ushort i) {
  auto bombCount = static_cast<ushort>(bombs.size());
  ushort columns = bombCount / rows;

  vector<int> indexes = {i - columns, i + columns};

  if (i % columns != 0) {
    indexes.push_back(i - columns - 1);
    indexes.push_back(i - 1);
    indexes.push_back(i + columns - 1);
  }

  if (i % columns != (columns - 1)) {
    indexes.push_back(i - columns + 1);
    indexes.push_back(i + 1);
    indexes.push_back(i + columns + 1);
  }

  ushort count = 0;
  for (auto index : indexes) {
    if (index < 0 || index >= bombCount) continue;

    if (bombs[index]) count++;
  }

  return count;
}

inline vector<char> prepareBoard(const vector<bool> &bombs, ushort rows) {
  assert(fitsUShort(bombs.size()));
  ushort cellCount = bombs.size();

  vector<char> cells;
  for (auto i = 0; i < cellCount; ++i) {
    if (bombs[i]) {
      cells.push_back('B');
    } else {
      auto count = countBombsAround(bombs, rows, i);
      cells.push_back(to_string(count).at(0));
    }
  }

  return cells;
}

// FIXME: Rewrite the board preparation so this function becomes unnecessary
inline vector<bool> getBools(ushort columns, ushort rows, const initializer_list<Point2D> &bombs) {
  vector<bool> bools(columns * rows, false);
  for (auto bomb : bombs) {
    bools[bomb.x + (bomb.y * columns)] = true;
  }
  return bools;
}

Board::Board(ushort columns, ushort rows, const Point2D &firstMove, const initializer_list<Point2D> &bombs)
    : firstMove(firstMove), cells(prepareBoard(getBools(columns, rows, bombs), rows)), rows(rows) {
  assert(bombs.size() > 0 && fitsUShort(bombs.size()));
  assert(firstMove.x < rows);
  assert(firstMove.y < columns);
}

ushort Board::bombCount() const {
  auto begin = cells.begin();
  auto end = cells.end();

  return count_if(begin, end, [](auto it) { return it == 'B'; });
}

char Board::cellAt(ushort index) const {
  assert(index < cells.size());
  return cells.at(index);
}
