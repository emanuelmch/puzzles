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

namespace CPic {
class BoardState {
public:
  BoardState() = default;

  BoardState(const std::vector<std::vector<Color>> &table) : internal(table) {}

  unsigned short countColorInColumn(unsigned short, Color) const;

  unsigned short countColorInRow(unsigned short, Color) const;

  void push_back(const std::vector<Color> &row) {
    internal.push_back(row);
  }

  unsigned long long int size() const {
    return internal.size();
  }

  std::vector<std::vector<Color>>::const_iterator begin() const {
    return internal.begin();
  }

  std::vector<std::vector<Color>>::const_iterator end() const {
    return internal.end();
  }

  const std::vector<Color> &at(unsigned short index) const {
    return internal.at(index);
  }

  std::vector<Color> &at(unsigned short index) {
    return internal.at(index);
  }

  const std::vector<Color> &operator[](unsigned short index) const {
    return internal.at(index);
  }

  std::vector<Color> &operator[](unsigned short index) {
    return internal.at(index);
  }

  bool operator==(const BoardState &other) const {
    return internal == other.internal;
  }

  bool operator!=(const BoardState &other) const {
    return internal != other.internal;
  }

private:
  std::vector<std::vector<Color>> internal;
};

inline BoardState pivotState(std::vector<std::vector<Color>> table) {
  std::vector<std::vector<Color>> result(table[0].size(), std::vector<Color>(table.size()));

  for (std::vector<Color>::size_type i = 0; i < table.size(); ++i) {
    for (std::vector<std::vector<Color>>::size_type j = 0; j < table[i].size(); ++j) {
      result[i][j] = table[j][i];
    }
  }

  return result;
}

inline BoardState emptyBoardState(unsigned long long int columnCount, unsigned long long int rowCount) {
  std::vector<std::vector<Color>> emptyBoard(columnCount, std::vector<Color>(rowCount));

  return emptyBoard;
}
}
