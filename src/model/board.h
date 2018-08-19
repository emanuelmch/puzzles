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

#include <cassert>
#include <vector>

//TODO: There should be a Color class/enum/whatever, instead of using ints for color
//TODO: After Color conversion, most of these ints should be changed to uints

namespace CPic {

enum Color { Blank, C0, C1 };

// FIXME: Kill this function
inline Color intToColor(int i) {
  switch (i) {
    case -1: return Blank;
    case 0: return C0;
    case 1: return C1;
    default: assert(! "Invalid Color enum value!");
  }
}
class Board {
public:

  Board(int colors, std::vector<std::vector<int>> columns, std::vector<std::vector<int>> rows);
  virtual ~Board();

  bool isValid();
  std::vector<std::vector<Color>> results;

  int colors;
  std::vector<std::vector<int>> columns;
  std::vector<std::vector<int>> rows;

  unsigned short countColorInColumn(unsigned short, Color);
  unsigned short countColorInRow(unsigned short, Color);
};

}
