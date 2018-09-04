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

typedef unsigned int uint;

void BoardLogger::log(const Board* board) const {
  // TODO: Improve logging
  int index = 0;
  for (auto itr = board->columns.cbegin(); itr != board->columns.cend(); ++itr) {
    std::cout << "Column " << ++index << ": ";
    auto values = *itr;
    for (auto itr2 = values.cbegin(); itr2 != values.cend(); ++itr2) {
      std::cout << (*itr2) << " ";
    }
    std::cout << std::endl;
  }

  index = 0;
  for (auto itr = board->rows.cbegin(); itr != board->rows.cend(); ++itr) {
    std::cout << "Row " << ++index << ": ";
    auto values = *itr;
    for (auto itr2 = values.cbegin(); itr2 != values.cend(); ++itr2) {
      std::cout << (*itr2) << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Final Board:" << std::endl;
  for (uint y = 0; y < board->rows.size(); ++y) {
    for (uint x = 0; x < board->columns.size(); ++x) {
          std::cout << board->results[x][y] << " ";
    }
    std::cout << std::endl;
  }
}
