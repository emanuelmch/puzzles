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
#include "board_data.h"

using namespace Sudoku;

using std::vector;

inline static BoardData createBoardEasy0() {
  Board board({{9, 0, 0, 5, 0, 3, 7, 0, 0},
               {3, 8, 7, 0, 1, 0, 5, 2, 0},
               {0, 0, 4, 0, 0, 0, 0, 9, 1},
               {0, 0, 3, 0, 8, 0, 0, 0, 9},
               {0, 6, 8, 3, 7, 9, 2, 1, 0},
               {2, 0, 0, 0, 5, 0, 8, 0, 0},
               {1, 3, 6, 0, 4, 0, 9, 0, 0},
               {0, 2, 9, 0, 0, 0, 0, 6, 5},
               {0, 0, 0, 6, 0, 7, 0, 0, 2}});
  Board solution({{9, 1, 2, 5, 6, 3, 7, 4, 8},
                  {3, 8, 7, 9, 1, 4, 5, 2, 6},
                  {6, 5, 4, 7, 2, 8, 3, 9, 1},
                  {4, 7, 3, 1, 8, 2, 6, 5, 9},
                  {5, 6, 8, 3, 7, 9, 2, 1, 4},
                  {2, 9, 1, 4, 5, 6, 8, 7, 3},
                  {1, 3, 6, 2, 4, 5, 9, 8, 7},
                  {7, 2, 9, 8, 3, 1, 4, 6, 5},
                  {8, 4, 5, 6, 9, 7, 1, 3, 2}});

  return BoardData("easy0", board, solution);
}

inline static BoardData createBoardEasy1() {
  Board board({{9, 0, 0, 5, 0, 3, 0, 0, 0},
               {3, 8, 0, 0, 0, 0, 5, 0, 0},
               {0, 0, 4, 0, 0, 0, 0, 9, 1},
               {0, 0, 3, 0, 8, 0, 0, 0, 9},
               {0, 6, 8, 3, 7, 9, 2, 1, 0},
               {2, 0, 0, 0, 5, 0, 8, 0, 0},
               {1, 3, 0, 0, 0, 0, 9, 0, 0},
               {0, 0, 9, 0, 0, 0, 0, 6, 5},
               {0, 0, 0, 6, 0, 7, 0, 0, 2}});
  Board solution({{9, 1, 2, 5, 6, 3, 7, 4, 8},
                  {3, 8, 7, 9, 1, 4, 5, 2, 6},
                  {6, 5, 4, 7, 2, 8, 3, 9, 1},
                  {4, 7, 3, 1, 8, 2, 6, 5, 9},
                  {5, 6, 8, 3, 7, 9, 2, 1, 4},
                  {2, 9, 1, 4, 5, 6, 8, 7, 3},
                  {1, 3, 6, 2, 4, 5, 9, 8, 7},
                  {7, 2, 9, 8, 3, 1, 4, 6, 5},
                  {8, 4, 5, 6, 9, 7, 1, 3, 2}});

  return BoardData("easy1", board, solution);
}

vector<BoardData> Sudoku::createEasyBoards() {
  return {createBoardEasy0(), createBoardEasy1()};
}
