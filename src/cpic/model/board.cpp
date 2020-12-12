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

#include "common/assertions.h"

using namespace CPic;

using std::map;
using std::vector;

Board::Board(vector<Color> colors, vector<vector<Clue>> columns, vector<vector<Clue>> rows)
    : colors(colors), colorCount(static_cast<int>(colors.size())), columnCount(static_cast<int>(columns.size())),
      rowCount(static_cast<int>(rows.size())), columns(columns), rows(rows) {}

Board::~Board() = default;

const Clue Board::clueForColumn(uint8_t column, Color color) const {
  for (auto clue : columns[column]) {
    if (clue.color == color) {
      return clue;
    }
  }

  ensure_never("Asked for a clue for a non-existing color");
  return Clue(Blank, 0, false);
}

const Clue Board::clueForRow(uint8_t row, Color color) const {
  for (auto clue : rows[row]) {
    if (clue.color == color) {
      return clue;
    }
  }

  ensure_never("Asked for a clue for a non-existing color");
  return Clue(Blank, 0, false);
}

uint8_t Board::countPossibilitiesForRow(uint8_t row, Color color) const {
  // TODO: Implement this in a more efficient manner
  uint8_t count = 0;

  for (auto col = 0; col < this->columnCount; ++col) {
    if (isPossibility(col, row, color)) {
      count++;
    }
  }

  return count;
}

bool Board::isPossibility(uint8_t col, uint8_t row, Color color) const {
  auto colClue = clueForColumn(col, color);
  if (colClue.amount == 0) return false;

  auto rowClue = clueForRow(row, color);
  return rowClue.amount != 0;
}
