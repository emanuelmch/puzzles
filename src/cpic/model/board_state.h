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

#include <cassert>
#include <iostream>
#include <vector>

#include "base_model.h"
#include "board.h"

namespace CPic {
class BoardRow {
  friend class BoardState;

public:
  BoardRow(const std::vector<Color> &values);

  inline void setColorAt(unsigned short column, Color color) {
    internal[column] = color;
  }

  inline ushort columnCount() const {
    return internal.size();
  }

  inline Color column(ushort column) const {
    return internal[column];
  }

  bool operator==(const BoardRow &other) const {
    return internal == other.internal;
  }

private:
  std::vector<Color> internal;
};

class BoardState {
public:
  BoardState() = default;
  explicit BoardState(const std::vector<std::vector<Color>> &rows);

  bool isValid(const Board *) const;
  unsigned short countColorInColumn(unsigned short, Color) const;
  unsigned short countColorInRow(unsigned short, Color) const;
  short findFirstInRow(unsigned short, Color) const;
  short findLastInRow(unsigned short, Color) const;

  inline void setColorAt(unsigned short column, unsigned short row, Color color) {
    rows.at(row).setColorAt(column, color);
  }

  inline ushort rowCount() const {
    return rows.size();
  }

  inline ushort columnCount() const {
    return rows[0].columnCount();
  }

  inline Color colorAt(unsigned short column, unsigned short row) const {
    return rows.at(row).column(column);
  }

  bool operator==(const BoardState &other) const {
    return rows == other.rows;
  }

  bool operator!=(const BoardState &other) const {
    return rows != other.rows;
  }

private:
  std::vector<BoardRow> rows;
};

inline BoardState emptyBoardState(ushort columnCount, ushort rowCount) {
  //FIXME: Implement this function properly
  if (columnCount == 5 && rowCount == 5) {
    return BoardState({{Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank}});
  }

  if (columnCount == 2 && rowCount == 2) {
    return BoardState({{Blank, Blank},
                       {Blank, Blank}});
  }

  if (columnCount == 2 && rowCount == 3) {
    return BoardState({{Blank, Blank},
                       {Blank, Blank},
                       {Blank, Blank}});
  }

  if (columnCount == 5 && rowCount == 10) {
    return BoardState({{Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank},
                       {Blank, Blank, Blank, Blank, Blank}});
  }

  std::cerr << "Couldn't build an empty state with " << columnCount << " columns and "
            << rowCount << " rows" << std::endl;
  throw -1;
}
}
