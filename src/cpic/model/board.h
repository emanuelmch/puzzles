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

#include <map>
#include <vector>

#include "base_model.h"

namespace CPic {

class Board {
public:
  Board(std::vector<Color>, std::vector<std::vector<Clue>> columns,
        std::vector<std::vector<Clue>> rows);
  virtual ~Board();

  const std::vector<Color> colors;

  const unsigned short colorCount;
  const unsigned short columnCount;
  const unsigned short rowCount;

  const Clue clueForColumn(unsigned short, Color) const;
  const Clue clueForRow(unsigned short, Color) const;

  // FIXME: Add Unit Tests for these two functions
  unsigned short countPossibilitiesForRow(unsigned short, Color) const;
  bool isPossibility(unsigned short col, unsigned short row, Color) const;

private:
  std::vector<std::vector<Clue>> columns;
  std::vector<std::vector<Clue>> rows;
};

}
