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

// TODO: Take columns of any value
BoardBuilder *BoardBuilder::column(vector<int> column) {
  assert(column.size() == 2);

  map<Color, int> colors;
  colors[C0] = column[0];
  colors[C1] = column[1];

  this->columns.push_back(colors);
  if (this->colorCount < column.size()) {
    this->colorCount = column.size();
  }

  return this;
}

// TODO: Take rows of any value
BoardBuilder *BoardBuilder::row(vector<int> row) {
  assert(row.size() == 2);

  map<Color, int> colors;
  colors[C0] = row[0];
  colors[C1] = row[1];

  this->rows.push_back(colors);
  if (this->colorCount < row.size()) {
    this->colorCount = row.size();
  }

  return this;
}

Board BoardBuilder::build() {
  std::vector<Color> colors;

  if (colorCount >= 1) colors.push_back(C0);
  if (colorCount >= 2) colors.push_back(C1);
  if (colorCount >= 3) colors.push_back(C2);
  if (colorCount >= 4) colors.push_back(C3);

  return Board(colors, columns, rows);
}
