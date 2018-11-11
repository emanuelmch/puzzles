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

#include "../model/board.h"

#include <string>
#include <vector>

namespace Sudoku {
struct BoardData {
public:
  BoardData(const std::string name, const Board &board, const Board &solution) :
          name(name), board(board), solution(solution) {}

  const std::string name;
  const Board board;
  const Board solution;
};

inline BoardData createBoardTrivial1_0() {
  Board board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
               {4, 5, 6, 7, 8, 9, 1, 2, 3},
               {7, 8, 9, 1, 2, 3, 4, 5, 6},
               {2, 3, 4, 5, 6, 7, 8, 9, 1},
               {5, 6, 7, 8, 9, 1, 2, 3, 4},
               {8, 9, 1, 2, 3, 4, 5, 6, 7},
               {3, 4, 5, 6, 7, 8, 9, 1, 2},
               {6, 7, 8, 9, 1, 2, 3, 4, 5},
               {0, 1, 2, 3, 4, 5, 6, 7, 8}});
  Board solution({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                  {4, 5, 6, 7, 8, 9, 1, 2, 3},
                  {7, 8, 9, 1, 2, 3, 4, 5, 6},
                  {2, 3, 4, 5, 6, 7, 8, 9, 1},
                  {5, 6, 7, 8, 9, 1, 2, 3, 4},
                  {8, 9, 1, 2, 3, 4, 5, 6, 7},
                  {3, 4, 5, 6, 7, 8, 9, 1, 2},
                  {6, 7, 8, 9, 1, 2, 3, 4, 5},
                  {9, 1, 2, 3, 4, 5, 6, 7, 8}});


  return BoardData("trivial1_0", board, solution);
}
}
