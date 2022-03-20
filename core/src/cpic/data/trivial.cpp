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

#include "../model/board_builder.h"

using std::vector;

using namespace CPic;

BoardData createBoardTrivial1_0() {
  auto board = BoardBuilder(1)
                   .column({5}, {true})
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
  BoardState solution = BoardState({{C0, C0, C0, C0, C0}, //
                                    {C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0},
                                    {C0, C0, C0, C0, C0}});

  return BoardData("trivial1_0", board, solution);
}

BoardData createBoardTrivial1_1() {
  auto board = BoardBuilder(2)
                   .column({0, 2}, {false, true})
                   ->column({0, 2}, {false, true})
                   ->row({0, 2}, {false, true})
                   ->row({0, 2}, {false, true})
                   ->build();
  BoardState solution = BoardState({{C1, C1}, //
                                    {C1, C1}});

  return BoardData("trivial1_1", board, solution);
}

vector<BoardData> CPic::createTrivialBoards() {
  return {createBoardTrivial1_0(), createBoardTrivial1_1()};
}
