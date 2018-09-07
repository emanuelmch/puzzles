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

#include "board_logger.h"

#include <iostream>

using namespace CPic;

using std::ostream;

typedef unsigned short ushort;

ostream &operator<<(ostream &output, Clue const &clue) {
  return output << clue.amount << " blocks of color " << clue.color;
}

void BoardLogger::log(const Board *board) const {
  // TODO: Improve logging
  for (ushort i = 0; i < board->columnCount; ++i) {
    std::cout << "Column " << i + 1 << ": ";
    std::cout << board->clueForColumn(i, C0) << " ";
    std::cout << board->clueForColumn(i, C1) << " ";
    std::cout << std::endl;
  }

  for (ushort i = 0; i < board->rowCount; ++i) {
    std::cout << "Row " << i + 1 << ": ";
    std::cout << board->clueForRow(i, C0) << " ";
    std::cout << board->clueForRow(i, C1) << " ";
    std::cout << std::endl;
  }

  std::cout << "Final Board:" << std::endl;
  for (ushort y = 0; y < board->rowCount; ++y) {
    for (ushort x = 0; x < board->columnCount; ++x) {
      std::cout << board->results[x][y] << " ";
    }
    std::cout << std::endl;
  }
}
