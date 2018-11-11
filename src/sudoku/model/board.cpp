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

#include <cassert>

using namespace Sudoku;

typedef unsigned short ushort;

Board::Board(std::vector<std::vector<ushort>> _values) {
  assert(_values.size() == 9);
  for (const auto &row: _values) {
    assert(row.size() == 9);
    for (auto value : row) {
      assert(value <= 9); // Only values 0-9 are accepted
      this->values.emplace_back(value);
    }
  }
}

bool Board::operator==(const Sudoku::Board &other) const {
  return values == other.values;
}

bool Board::operator!=(const Sudoku::Board &other) const {
  return values != other.values;
}

ushort Board::firstEmptyCell() const {
  for (ushort i = 0; i < values.size(); ++i) {
    auto value = values[i];
    if (value == 0) {
      return i;
    }
  }

  //FIXME: Should return UNSIGNED_SHORT_MAX
  return static_cast<ushort>(values.size());
}

//FIXME: Implement isValid
bool Board::isValid() const {
  return true;
}

bool Board::isFull() const {
  //TODO: Replace this with something from algorithms
  for (auto value : values) {
    if (value == 0) {
      return false;
    }
  }

  return true;
}

ushort Board::getCell(unsigned short index) const {
  return values[index];
}

void Board::setCell(ushort index, ushort value) {
  values[index] = value;
}


