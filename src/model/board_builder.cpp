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

#include "board_builder.h"

#include <cassert>

using namespace CPic;

using std::map;
using std::vector;

typedef unsigned short ushort;

BoardBuilder::BoardBuilder(ushort colorCount) {
    assert(colorCount > 0 && colorCount < 4);

    if (colorCount >= 1) colors.push_back(C0);
    if (colorCount >= 2) colors.push_back(C1);
    if (colorCount >= 3) colors.push_back(C2);
    if (colorCount >= 4) colors.push_back(C3);
}

BoardBuilder *BoardBuilder::column(vector<int> column) {
  map<Color, int> colorColumn;

  for (ushort i = 0; i < colors.size(); ++i) {
    auto color = colors[i];
    if (column.size() > i) {
      colorColumn[color] = column[i];
    } else {
      colorColumn[color] = 0;
    }
  }

  this->columns.push_back(colorColumn);

  return this;
}

BoardBuilder *BoardBuilder::row(vector<int> row) {
  map<Color, int> colorRow;

  for (ushort i = 0; i < colors.size(); ++i) {
    auto color = colors[i];
    if (row.size() > i) {
      colorRow[color] = row[i];
    } else {
      colorRow[color] = 0;
    }
  }

  this->rows.push_back(colorRow);

  return this;
}

Board BoardBuilder::build() {
  return Board(colors, columns, rows);
}
