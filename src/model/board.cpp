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

using namespace CPic;

using std::vector;

typedef unsigned short ushort;

inline int cellsInColumnByColor(Board *, ushort column, Color color);
inline int cellsInRowByColor(Board *, ushort row, Color color);

Board::Board(int colors, vector<vector<int>> columns, vector<vector<int>> rows)
              : colors(colors), columns(columns), rows(rows) {
  const ushort columnCount = columns.size();
  const ushort rowCount = rows.size();

  for (ushort x = 0; x < rowCount; x++) {
    std::vector<Color> row;
    for (ushort y = 0; y < columnCount; y++) {
      row.push_back(Blank);
    }
    this->results.push_back(row);
  }
}

Board::~Board() {}

bool Board::isValid() {
  for (ushort i = 0; i < columns.size(); ++i) {
    for (ushort color = 0; color < colors; ++color) {
      auto count = cellsInColumnByColor(this, i, intToColor(color));
      if (count > columns[i][color]) {
        return false;
      }
    }
  }

  for (ushort i = 0; i < rows.size(); ++i) {
    for (ushort color = 0; color < colors; ++color) {
      auto count = cellsInRowByColor(this, i, intToColor(color));
      if (count > rows[i][color]) {
        return false;
      }
    }
  }

  return true;
}

int cellsInColumnByColor(Board *board, ushort column, Color color) {
  const auto results = board->results;

  int count = 0;

  for (ushort i = 0; i < results[column].size(); ++i) {
    if (results[column][i] == color)
      count++;
  }

  return count;
}

int cellsInRowByColor(Board *board, ushort row, Color color) {
  const auto results = board->results;

  int count = 0;

  for (ushort i = 0; i < results.size(); ++i) {
    if (results[i][row] == color)
      count++;
  }

  return count;
}
