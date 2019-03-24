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

#pragma once

#include <vector>

#include "base_model.h"
#include "board.h"

namespace CPic {

class BoardColumn {
public:
  explicit BoardColumn(const unsigned short size) : internal(size) {}
  explicit BoardColumn(const std::vector<Color> &values);

  void setColorAt(unsigned short index, Color color) {
    internal[index] = color;
  }

  Color row(unsigned short index) const {
    return internal[index];
  }

  unsigned short rowCount() const {
    return static_cast<unsigned short>(internal.size());
  }

  const std::vector<Color>::const_iterator begin() const {
    return internal.begin();
  }

  const std::vector<Color>::const_iterator end() const {
    return internal.end();
  }

  bool operator==(const BoardColumn &other) const {
    return internal == other.internal;
  }

private:
  std::vector<Color> internal;
};

class BoardState {
public:
  BoardState() = default;
  explicit BoardState(std::vector<BoardColumn> table) : internal(std::move(table)) {}

  bool isValid(const Board *) const;
  unsigned short countColorInColumn(unsigned short, Color) const;
  unsigned short countColorInRow(unsigned short, Color) const;

  void push_back(const BoardColumn &row) {
    internal.push_back(row);
  }

  void setColorAt(unsigned short column, unsigned short row, Color color) {
    internal.at(column).setColorAt(row, color);
  }

  unsigned long long int rowCount() const {
    return internal[0].rowCount();
  }

  unsigned long long int columnCount() const {
    return internal.size();
  }

  const std::vector<BoardColumn>::const_iterator begin() const {
    return internal.begin();
  }

  const std::vector<BoardColumn>::const_iterator end() const {
    return internal.end();
  }

  Color colorAt(unsigned short column, unsigned short row) const {
    return internal.at(column).row(row);
  }

  bool operator==(const BoardState &other) const {
    return internal == other.internal;
  }

  bool operator!=(const BoardState &other) const {
    return internal != other.internal;
  }

private:
  std::vector<BoardColumn> internal;
};

inline BoardState pivotState(std::vector<std::vector<Color>> table) {
  auto rowCount = static_cast<unsigned short>(table.size());
  auto columnCount = static_cast<unsigned short>(table[0].size());
  std::vector<BoardColumn> result(columnCount, BoardColumn(rowCount));

  for (unsigned short i = 0; i < rowCount; ++i) {
    for (unsigned short j = 0; j < columnCount; ++j) {
      result[i].setColorAt(j, table[j][i]);
    }
  }

  return BoardState(result);
}

inline BoardState emptyBoardState(unsigned short columnCount, unsigned short rowCount) {
  std::vector<BoardColumn> emptyBoard(columnCount, BoardColumn(rowCount));

  return BoardState(emptyBoard);
}
}
