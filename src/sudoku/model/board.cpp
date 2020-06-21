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
#include <limits>

using namespace Sudoku;

static const int SIZE = 9;

Board::Board(std::vector<std::vector<uint8_t>> _values) {
  assert(_values.size() == SIZE);
  for (const auto &row : _values) {
    assert(row.size() == SIZE);
    for (auto value : row) {
      assert(value <= SIZE); // Only values 0-9 are accepted
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

uint8_t Board::firstEmptyCell() const {
  for (uint8_t i = 0; i < values.size(); ++i) {
    auto value = values[i];
    if (value == 0) {
      return i;
    }
  }

  return std::numeric_limits<uint8_t>::max();
}

bool Board::isValid() const {
  // Check for repetition on lines
  for (auto min = 0; min < (SIZE * SIZE); min += SIZE) {
    bool used[SIZE] = {
        false,
    };

    for (auto i = 0; i < SIZE; ++i) {
      auto value = values[min + i];
      if (value == 0) continue;
      if (used[value - 1]) return false;
      used[value - 1] = true;
    }
  }

  // Check for repetition on columns
  for (auto min = 0; min < SIZE; min++) {
    bool used[SIZE] = {
        false,
    };

    for (auto i = 0; i < SIZE; ++i) {
      auto value = values[min + (SIZE * i)];
      if (value == 0) continue;
      if (used[value - 1]) return false;
      used[value - 1] = true;
    }
  }

  // Check for repetitions on squares
  for (auto i = 0; i < SIZE; i += 3) {
    for (auto j = 0; j < SIZE; j += 3) {
      const auto first = i + (SIZE * j);
      const auto indices = {0, 1, 2, 9, 10, 11, 18, 19, 20};
      bool used[SIZE] = {
          false,
      };

      for (auto index : indices) {
        auto value = values[first + index];
        if (value == 0) continue;
        if (used[value - 1]) return false;
        used[value - 1] = true;
      }
    }
  }

  return true;
}

bool Board::isFull() const {
  // TODO: Replace this with something from algorithms
  for (auto value : values) {
    if (value == 0) {
      return false;
    }
  }

  return true;
}

uint8_t Board::getCell(uint8_t index) const {
  return values[index];
}

void Board::setCell(uint8_t index, uint8_t value) {
  values[index] = value;
}
