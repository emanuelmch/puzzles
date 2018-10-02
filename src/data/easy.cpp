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

#include "easy.h"

#include "../model/board_builder.h"

using std::vector;

using namespace CPic;

BoardData createBoardEasy1_0() {
  auto board = BoardBuilder(1).column({5}, {true})
          ->column({5}, {true})
          ->column({5}, {true})
          ->column({5}, {true})
          ->column({5}, {true})
          ->row({5}, {true})
          ->row({5}, {true})
          ->row({5}, {true})
          ->row({5}, {true})
          ->row({5}, {true})
          ->build();
  BoardState solution = pivotState({{C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0}});

  return BoardData("easy1_0", board, solution);
}

BoardData createBoardEasy1_1() {
  auto board = BoardBuilder(2).column({2, 3}, {true, true})
          ->column({2, 3}, {true, true})
          ->column({2, 3}, {true, true})
          ->column({5}, {true})
          ->column({5}, {true})
          ->row({5}, {true})
          ->row({5}, {true})
          ->row({2, 3}, {true, true})
          ->row({2, 3}, {true, true})
          ->row({2, 3}, {true, true})
          ->build();
  BoardState solution = pivotState({{C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0},
                                    {C1, C1, C1, C0, C0},
                                    {C1, C1, C1, C0, C0},
                                    {C1, C1, C1, C0, C0}});

  return BoardData("easy1_1", board, solution);
}

vector<BoardData> CPic::createEasyBoards() {
  return {createBoardEasy1_0(), createBoardEasy1_1()};
}
