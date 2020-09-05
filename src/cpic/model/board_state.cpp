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

#include "common/numbers.h"

#include <algorithm>
#include <cassert>
#include <cstdint>

using std::count_if;
using std::vector;

using namespace CPic;
using namespace Puzzles;

BoardRow::BoardRow(const vector<Color> &values) : internal(values) {
  assert(values.empty() == false);
  assert(Numbers::fitsUShort(values.size()));
}

int8_t findFirstColorInColumn(const BoardState *state, uint_fast8_t column, Color color);
int8_t findLastColorInColumn(const BoardState *state, uint_fast8_t column, Color color);

BoardState::BoardState(uint8_t columnCount, uint8_t rowCount) {
  vector<Color> column(columnCount, Blank);

  for (auto i = 0; i < rowCount; ++i) {
    this->rows.emplace_back(BoardRow(column));
  }
}

BoardState::BoardState(const vector<vector<Color>> &rows) {
  assert(rows.empty() == false);
  assert(Numbers::fitsUShort(rows.size()));

  for (const auto &row : rows) {
    this->rows.emplace_back(row);
  }
}

bool BoardState::isValid(const CPic::Board *board) const {
  // Has too many of a color in a column?
  for (auto i = 0; i < board->columnCount; ++i) {
    for (auto color : board->colors) {
      auto count = countColorInColumn(i, color);
      if (count > board->clueForColumn(i, color).amount) {
        return false;
      }
    }
  }

  // Has too many of a color in a row?
  for (auto i = 0; i < board->rowCount; ++i) {
    for (auto color : board->colors) {
      auto count = countColorInRow(i, color);
      if (count > board->clueForRow(i, color).amount) {
        return false;
      }
    }
  }

  // Breaks the contiguity clue in a column?
  for (auto i = 0; i < board->columnCount; ++i) {
    for (auto color : board->colors) {
      auto clue = board->clueForColumn(i, color);
      if (clue.amount == 1) continue;

      auto _first = findFirstColorInColumn(this, i, color);
      if (_first < 0) continue;

      assert(Numbers::fitsUnsignedInt8(_first));
      auto first = static_cast<uint8_t>(_first);
      auto last = findLastColorInColumn(this, i, color);

      if (clue.contiguous) {
        if ((last - first) >= clue.amount) {
          return false;
        } else {
          for (uint8_t j = first + 1; j < last; ++j) {
            auto result = colorAt(i, j);
            if (result != clue.color && result != Blank) {
              return false;
            }
          }
        }
      } else {
        auto count = countColorInColumn(i, color);
        if (count != clue.amount) continue;
        if ((last - first) <= (clue.amount - 1)) {
          return false;
        }
      }
    }
  }

  // Breaks the contiguity clue in a row?
  for (auto i = 0; i < board->rowCount; ++i) {
    for (auto color : board->colors) {
      auto clue = board->clueForRow(i, color);
      if (clue.amount == 1) continue;

      auto first = findFirstInRow(i, color);
      if (first == -1) continue;
      auto last = findLastInRow(i, color);

      if (clue.contiguous) {
        if ((last - first) >= clue.amount) {
          return false;
        } else {
          for (auto j = static_cast<uint8_t>(first + 1); j < last; ++j) {
            auto result = colorAt(j, i);
            if (result != clue.color && result != Blank) {
              return false;
            }
          }
        }
      } else {
        auto count = countColorInRow(i, color);
        if (count != clue.amount) continue;
        if ((last - first) <= (clue.amount - 1)) {
          return false;
        }
      }
    }
  }

  return true;
}

int8_t findFirstColorInColumn(const BoardState *state, uint8_t column, Color color) {
  auto size = static_cast<uint8_t>(state->rowCount());
  for (auto i = 0; i < size; ++i) {
    if (state->colorAt(column, i) == color) {
      return i;
    }
  }
  return -1;
}

int8_t findLastColorInColumn(const BoardState *state, uint8_t column, Color color) {
  auto size = static_cast<int8_t>(state->rowCount());
  auto index = -1;
  for (auto i = 0; i < size; ++i) {
    if (state->colorAt(column, i) == color) {
      index = i;
    }
  }
  return index;
}

uint8_t BoardState::countColorInColumn(uint8_t column, Color color) const {
  auto begin = rows.begin();
  auto end = rows.end();
  return count_if(begin, end, [column, color](auto it) { return it.column(column) == color; });
}

uint8_t BoardState::countColorInRow(uint8_t index, Color color) const {
  auto row = this->rows.at(index);
  auto begin = row.internal.begin();
  auto end = row.internal.end();

  return static_cast<uint8_t>(count_if(begin, end, [color](auto it) { return it == color; }));
}

int8_t BoardState::findFirstInRow(uint8_t index, Color color) const {
  assert(rows.size() > index);

  auto row = rows[index];
  auto result = std::find(row.internal.begin(), row.internal.end(), color);
  if (result == row.internal.end()) {
    return -1;
  } else {
    return result - row.internal.begin();
  }
}

int8_t BoardState::findLastInRow(uint8_t index, Color color) const {
  assert(rows.size() > index);

  auto row = rows[index];
  auto result = std::find(row.internal.rbegin(), row.internal.rend(), color);
  return row.internal.rend() - result - 1;
}
