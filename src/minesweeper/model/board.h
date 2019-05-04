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

#include <iostream>
#include <sys/types.h>
#include <vector>

namespace Minesweeper {

struct Point2D {
  const int x;
  const int y;

  Point2D(int x, int y) : x(x), y(y) {}

  bool operator==(const Point2D &other) { return x == other.x && y == other.y; }
};

std::ostream &operator<<(std::ostream &, const Point2D &);

class Board {
public:
  Board(const std::vector<bool> &bombs, ushort rows, const Point2D &firstMove);

  const Point2D firstMove;

  ushort bombCount() const;
  ushort cellCount() const { return cells.size(); }
  ushort columnCount() const { return cells.size() / rows; }
  ushort rowCount() const { return rows; }

  // FIXME: I've been misusing this motherfucker
  char cellAt(ushort) const;

private:
  const std::vector<char> cells;
  const ushort rows;
};
}
