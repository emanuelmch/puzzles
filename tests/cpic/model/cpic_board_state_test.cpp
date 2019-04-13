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
#include "cpic/model/board_state.h"

#include <gtest/gtest.h>

using namespace CPic;

TEST(BoardState, ShouldCreateASquareState) {
  BoardState board({{C0, C1},
                    {C1, C0}});

  ASSERT_EQ(board.columnCount(), 2);
  ASSERT_EQ(board.rowCount(), 2);

  EXPECT_EQ(board.colorAt(0, 0), C0);
  EXPECT_EQ(board.colorAt(0, 1), C1);
  EXPECT_EQ(board.colorAt(1, 0), C1);
  EXPECT_EQ(board.colorAt(1, 1), C0);
}

TEST(BoardState, ShouldCreateAWideState) {
  BoardState board({{C0, C1, C0},
                    {C1, C0, C1}});

  ASSERT_EQ(board.columnCount(), 3);
  ASSERT_EQ(board.rowCount(), 2);

  EXPECT_EQ(board.colorAt(0, 0), C0);
  EXPECT_EQ(board.colorAt(0, 1), C1);
  EXPECT_EQ(board.colorAt(1, 0), C1);
  EXPECT_EQ(board.colorAt(1, 1), C0);
  EXPECT_EQ(board.colorAt(2, 0), C0);
  EXPECT_EQ(board.colorAt(2, 1), C1);
}

TEST(BoardState, ShouldCreateATallState) {
  BoardState board({{C0, C1},
                    {C1, C0},
                    {C0, C1}});

  ASSERT_EQ(board.columnCount(), 2);
  ASSERT_EQ(board.rowCount(), 3);

  EXPECT_EQ(board.colorAt(0, 0), C0);
  EXPECT_EQ(board.colorAt(0, 1), C1);
  EXPECT_EQ(board.colorAt(0, 2), C0);
  EXPECT_EQ(board.colorAt(1, 0), C1);
  EXPECT_EQ(board.colorAt(1, 1), C0);
  EXPECT_EQ(board.colorAt(1, 2), C1);
}

TEST(BoardState, ShouldFindFirstInRowWhenInTheStart) {
  BoardState board({{C1, C1, C1}});

  EXPECT_EQ(board.findFirstInRow(0, C1), 0);
}

TEST(BoardState, ShouldFindFirstInRowWhenInTheMiddle) {
  BoardState board({{C0, C1, C1}});

  EXPECT_EQ(board.findFirstInRow(0, C1), 1);
}

TEST(BoardState, ShouldFindFirstInRowWhenInTheEnd) {
  BoardState board({{C0, C0, C1}});

  EXPECT_EQ(board.findFirstInRow(0, C1), 2);
}

TEST(BoardState, ShouldFindFirstInRowWhenNotThere) {
  BoardState board({{C0, C0, C0}});

  EXPECT_EQ(board.findFirstInRow(0, C1), -1);
}

TEST(BoardState, ShouldfindLastInRowWhenInTheStart) {
  BoardState board({{C1, C0, C0}});

  EXPECT_EQ(board.findLastInRow(0, C1), 0);
}

TEST(BoardState, ShouldfindLastInRowWhenInTheMiddle) {
  BoardState board({{C1, C1, C0}});

  EXPECT_EQ(board.findLastInRow(0, C1), 1);
}

TEST(BoardState, ShouldfindLastInRowWhenInTheEnd) {
  BoardState board({{C1, C1, C1}});

  EXPECT_EQ(board.findLastInRow(0, C1), 2);
}

TEST(BoardState, ShouldfindLastInRowWhenNotThere) {
  BoardState board({{C0, C0, C0}});

  EXPECT_EQ(board.findLastInRow(0, C1), -1);
}
