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

#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "base_model.h"
#include "board.h"

namespace CPic {
class BoardRow {
  friend class BoardState;

public:
  BoardRow(const std::vector<Color> &values);

  inline void setColorAt(uint8_t column, Color color) { internal[column] = color; }

  inline uint8_t columnCount() const { return internal.size(); }

  inline Color column(uint8_t column) const { return internal[column]; }

  bool operator==(const BoardRow &other) const { return internal == other.internal; }

private:
  std::vector<Color> internal;
};

class BoardState {
public:
  BoardState() = default;
  BoardState(uint8_t columnCount, uint8_t rowCount);
  explicit BoardState(const std::vector<std::vector<Color>> &rows);

  bool isValid(const Board *) const;
  uint8_t countColorInColumn(uint8_t, Color) const;
  uint8_t countColorInRow(uint8_t, Color) const;
  int8_t findFirstInRow(uint8_t, Color) const;
  int8_t findLastInRow(uint8_t, Color) const;

  inline void setColorAt(uint8_t column, uint8_t row, Color color) { rows.at(row).setColorAt(column, color); }

  inline uint8_t rowCount() const { return rows.size(); }

  inline uint8_t columnCount() const { return rows[0].columnCount(); }

  inline Color colorAt(uint8_t column, uint8_t row) const { return rows.at(row).column(column); }
  bool operator==(const BoardState &other) const { return rows == other.rows; }

  bool operator!=(const BoardState &other) const { return rows != other.rows; }

private:
  std::vector<BoardRow> rows;
};
}
