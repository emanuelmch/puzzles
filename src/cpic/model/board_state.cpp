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

#include <algorithm>
#include <cassert>

#include "../../common/numbers.h"

typedef unsigned short ushort;

using std::count_if;
using std::vector;

using namespace CPic;
using namespace Puzzles;

BoardColumn::BoardColumn(const vector<Color> &values) : internal(values) {
  assert(values.empty() == false);
  assert(Numbers::fitsUShort(static_cast<unsigned long long int>(values.size())));
}

short findFirstColorInColumn(const BoardState *state, ushort column, Color color);
short findLastColorInColumn(const BoardState *state, ushort column, Color color);
short findFirstColorInRow(const BoardState *state, ushort row, Color color);
short findLastColorInRow(const BoardState *state, ushort row, Color color);

bool BoardState::isValid(const CPic::Board *board) const {
  // Has too many of a color in a column?
  for (ushort i = 0; i < board->columnCount; ++i) {
    for (auto color : board->colors) {
      auto count = countColorInColumn(i, color);
      if (count > board->clueForColumn(i, color).amount) {
        return false;
      }
    }
  }

  // Has too many of a color in a row?
  for (ushort i = 0; i < board->rowCount; ++i) {
    for (auto color : board->colors) {
      auto count = countColorInRow(i, color);
      if (count > board->clueForRow(i, color).amount) {
        return false;
      }
    }
  }

  // Breaks the contiguity clue in a column?
  for (ushort i = 0; i < board->columnCount; ++i) {
    for (auto color : board->colors) {
      auto clue = board->clueForColumn(i, color);
      if (clue.amount == 1) continue;

      auto _first = findFirstColorInColumn(this, i, color);
      if (_first < 0) continue;

      assert(Numbers::fitsUShort(_first));
      auto first = static_cast<ushort>(_first);
      auto last = findLastColorInColumn(this, i, color);

      if (clue.contiguous) {
        if ((last - first) >= clue.amount) {
          return false;
        } else {
          // FIXME: Shouldn't bother test the case `j == first`
          for (ushort j = first; j < last; ++j) {
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
  for (ushort i = 0; i < board->rowCount; ++i) {
    for (auto color : board->colors) {
      auto clue = board->clueForRow(i, color);
      if (clue.amount == 1) continue;

      auto first = findFirstColorInRow(this, i, color);
      if (first == -1) continue;
      auto last = findLastColorInRow(this, i, color);

      if (clue.contiguous) {
        if ((last - first) >= clue.amount) {
          return false;
        } else {
          for (auto j = static_cast<ushort>(first + 1); j < last; ++j) {
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

short findFirstColorInColumn(const BoardState *state, ushort column, Color color) {
  auto size = static_cast<ushort>(state->rowCount());
  for (ushort i = 0; i < size; ++i) {
    if (state->colorAt(column, i) == color) {
      return i;
    }
  }
  return -1;
}

short findLastColorInColumn(const BoardState *state, ushort column, Color color) {
  auto size = static_cast<short>(state->rowCount());
  short index = -1;
  for (ushort i = 0; i < size; ++i) {
    if (state->colorAt(column, i) == color) {
      index = i;
    }
  }
  return index;
}

short findFirstColorInRow(const BoardState *state, ushort row, Color color) {
  auto size = static_cast<ushort>(state->columnCount());
  for (ushort i = 0; i < size; ++i) {
    if (state->colorAt(i, row) == color) {
      return i;
    }
  }
  return -1;
}

short findLastColorInRow(const BoardState *state, ushort row, Color color) {
  auto size = static_cast<ushort>(state->columnCount());
  short index = -1;

  for (ushort i = 0; i < size; ++i) {
    if (state->colorAt(i, row) == color) {
      index = i;
    }
  }
  return index;
}

ushort BoardState::countColorInColumn(ushort index, Color color) const {
  auto column = this->internal.at(index);
  auto begin = column.begin();
  auto end = column.end();

  return static_cast<ushort>(count_if(begin, end, [color](auto it) {
    return it == color;
  }));
}

ushort BoardState::countColorInRow(ushort row, Color color) const {
  return static_cast<ushort>(count_if(begin(), end(), [color, row](auto it) {
    return it.row(row) == color;
  }));
}

short BoardState::findFirstInRow(ushort row, Color color) const {
  for (ushort col = 0; col < internal.size(); col++) {
    if (internal[col].row(row) == color) {
      return col;
    }
  }

  return -1;
}

short BoardState::findLastInRow(unsigned short row, Color color) const {
  auto size = static_cast<short>(internal.size() - 1);
  for (short col = size; col >= 0; col--) {
    if (internal[col].row(row) == color) {
      return col;
    }
  }

  return -1;
}
