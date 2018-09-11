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

#include "board.h"

#include <algorithm>
#include <cassert>

using namespace CPic;

using std::count_if;
using std::map;
using std::vector;

typedef unsigned short ushort;

short findFirstColorInColumn(BoardState results, ushort column, Color color);
short findLastColorInColumn(BoardState results, ushort column, Color color);
short findFirstColorInRow(BoardState results, ushort row, Color color);
short findLastColorInRow(BoardState results, ushort row, Color color);

Board::Board(vector<Color> colors, vector<vector<Clue>> columns, vector<vector<Clue>> rows)
        : colors(colors),
          colorCount(static_cast<int>(colors.size())),
          columnCount(static_cast<int>(columns.size())),
          rowCount(static_cast<int>(rows.size())),
          columns(columns),
          rows(rows) {
  for (ushort x = 0; x < columnCount; x++) {
    std::vector<Color> column;
    for (ushort y = 0; y < rowCount; y++) {
      column.push_back(Blank);
    }
    this->results.push_back(column);
  }
}

Board::~Board() = default;

bool Board::isValid() {
  // Has too many of a color in a column?
  for (ushort i = 0; i < columns.size(); ++i) {
    for (auto color : colors) {
      auto count = countColorInColumn(i, color);
      if (count > clueForColumn(i, color).amount) {
        return false;
      }
    }
  }

  // Has too many of a color in a row?
  for (ushort i = 0; i < rows.size(); ++i) {
    for (auto color : colors) {
      auto count = countColorInRow(i, color);
      if (count > clueForRow(i, color).amount) {
        return false;
      }
    }
  }

  // Breaks the contiguity clue in a column?
  for (ushort i = 0; i < columns.size(); ++i) {
    for (auto color : colors) {
      auto clue = clueForColumn(i, color);
      if (clue.amount == 1) continue;

      auto first = findFirstColorInColumn(results, i, color);
      if (first == -1) continue;
      auto last = findLastColorInColumn(results, i, color);

      if (clue.contiguous) {
        if ((last - first) >= clue.amount) {
          return false;
        } else {
          for (int j = first + 1; j < last; ++j) {
            auto result = results[i][j];
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
  for (ushort i = 0; i < rows.size(); ++i) {
    for (auto color : colors) {
      auto clue = clueForRow(i, color);
      if (clue.amount == 1) continue;

      auto first = findFirstColorInRow(results, i, color);
      if (first == -1) continue;
      auto last = findLastColorInRow(results, i, color);

      if (clue.contiguous) {
        if ((last - first) >= clue.amount) {
          return false;
        } else {
          for (int j = first + 1; j < last; ++j) {
            auto result = results[j][i];
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

short findFirstColorInColumn(BoardState results, ushort column, Color color) {
  for (short i = 0; i < results[column].size(); ++i) {
    if (results[column][i] == color) {
      return i;
    }
  }
  return -1;
}

short findLastColorInColumn(BoardState results, ushort column, Color color) {
  short index = -1;
  for (short i = 0; i < results[column].size(); ++i) {
    if (results[column][i] == color) {
      index = i;
    }
  }
  return index;
}

short findFirstColorInRow(BoardState results, ushort row, Color color) {
  for (short i = 0; i < results.size(); ++i) {
    if (results[i][row] == color) {
      return i;
    }
  }
  return -1;
}

short findLastColorInRow(BoardState results, ushort row, Color color) {
  short index = -1;
  for (short i = 0; i < results.size(); ++i) {
    if (results[i][row] == color) {
      index = i;
    }
  }
  return index;
}

ushort Board::countColorInColumn(ushort column, Color color) const {
  auto begin = results[column].begin();
  auto end = results[column].end();

  return static_cast<ushort>(count_if(begin, end, [color](auto it) {
    return it == color;
  }));
}

ushort Board::countColorInRow(ushort row, Color color) const {
  auto begin = results.begin();
  auto end = results.end();

  return static_cast<ushort>(count_if(begin, end, [color, row](auto it) {
    return it[row] == color;
  }));
}

const Clue Board::clueForColumn(ushort column, Color color) const {
  for (auto clue : columns[column]) {
    if (clue.color == color) {
      return clue;
    }
  }

  assert(!"Asked for a clue for a non-existing color");
}

const Clue Board::clueForRow(ushort row, Color color) const {
  for (auto clue : rows[row]) {
    if (clue.color == color) {
      return clue;
    }
  }

  assert(!"Asked for a clue for a non-existing color");
}
