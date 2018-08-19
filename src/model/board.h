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

#pragma once

#include <map>
#include <vector>

namespace CPic {

enum Color { Blank, C0, C1, C2, C3 };

class Board {
public:

  Board(std::vector<Color>, std::vector<std::map<Color, int>> columns, std::vector<std::map<Color, int>> rows);
  virtual ~Board();

  bool isValid();
  std::vector<std::vector<Color>> results;
  std::vector<Color> colors;

  int colorCount;
  int columnCount;
  int rowCount;

  unsigned short countColorInColumn(unsigned short, Color) const;
  unsigned short countColorInRow(unsigned short, Color) const;

  unsigned short clueForColumn(unsigned short, Color) const;
  unsigned short clueForRow(unsigned short, Color) const;

private:
  std::vector<std::map<Color, int>> columns;
  std::vector<std::map<Color, int>> rows;
};

}
