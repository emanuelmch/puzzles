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

#include "model/board_builder.h"

#include <gtest/gtest.h>

using namespace CPic;

TEST(BoardBuilder, ShouldNotComplainOnValidMissingColumnClues) {
  auto board = BoardBuilder(2).column({2})
                              ->column({0, 2})
                              ->row({1, 1})
                              ->row({1, 1})
                              ->build();

  EXPECT_EQ(board.clueForColumn(0, C0), 2);
  EXPECT_EQ(board.clueForColumn(0, C1), 0);
  EXPECT_EQ(board.clueForColumn(1, C0), 0);
  EXPECT_EQ(board.clueForColumn(1, C1), 2);
}

TEST(BoardBuilder, ShouldNotComplainOnExtraColumnClues) {
  auto board = BoardBuilder(2).column({2, 0, 0, 0})
                              ->column({0, 2, 0, 0})
                              ->row({1, 1})
                              ->row({1, 1})
                              ->build();

  EXPECT_EQ(board.clueForColumn(0, C0), 2);
  EXPECT_EQ(board.clueForColumn(0, C1), 0);
  EXPECT_EQ(board.clueForColumn(1, C0), 0);
  EXPECT_EQ(board.clueForColumn(1, C1), 2);
}

TEST(BoardBuilder, ShouldNotComplainOnValidMissingRowClues) {
  auto board = BoardBuilder(2).column({1, 1})
                              ->column({1, 1})
                              ->row({2})
                              ->row({0, 2})
                              ->build();

  EXPECT_EQ(board.clueForRow(0, C0), 2);
  EXPECT_EQ(board.clueForRow(0, C1), 0);
  EXPECT_EQ(board.clueForRow(1, C0), 0);
  EXPECT_EQ(board.clueForRow(1, C1), 2);
}

TEST(BoardBuilder, ShouldNotComplainOnExtraRowClues) {
  auto board = BoardBuilder(2).column({1, 1})
                              ->column({1, 1})
                              ->row({2, 0, 0, 0})
                              ->row({0, 2, 0, 0})
                              ->build();

  EXPECT_EQ(board.clueForRow(0, C0), 2);
  EXPECT_EQ(board.clueForRow(0, C1), 0);
  EXPECT_EQ(board.clueForRow(1, C0), 0);
  EXPECT_EQ(board.clueForRow(1, C1), 2);
}
