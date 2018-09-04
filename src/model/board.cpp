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

using namespace CPic;

using std::count_if;
using std::vector;

typedef unsigned int uint;

Board::Board(int colors, vector<vector<int>> columns, vector<vector<int>> rows)
              : colors(colors), columns(columns), rows(rows) {
  const uint columnCount = columns.size();
  const uint rowCount = rows.size();

  for (uint x = 0; x < rowCount; x++) {
    std::vector<int> row;
    for (uint y = 0; y < columnCount; y++) {
      row.push_back(COLOR_BLANK);
    }
    this->results.push_back(row);
  }
}

Board::~Board() {}

uint Board::blankCellsOnColumn(uint column) {
  //TODO: Don't calculate this every time
  auto isBlank = [](int cell) { return cell == COLOR_BLANK; };
  auto count = count_if(results[column].cbegin(), results[column].cend(), isBlank);
  return static_cast<uint>(count);
}

vector<uint> Board::missingColorsOnColumn(uint column) {
  //TODO: Don't calculate this every time. Oh, and clean this awful mess...
  vector<int> missing = columns[column];

  uint rowCount = static_cast<uint>(this->rows.size());
  for (uint row = 0; row < rowCount; ++row) {
    int color = this->results[row][column];
    if (color != COLOR_BLANK) {
      auto index = static_cast<size_t>(color);
      missing[index]--;
    }
  }

  vector<uint> result;
  for (auto itr = missing.cbegin(); itr != missing.cend(); ++itr) {
    result.push_back(static_cast<uint>(*itr));
  }
  return result;
}
