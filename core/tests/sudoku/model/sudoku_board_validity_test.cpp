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

#include "test_data.h"

#include <gtest/gtest.h>

using namespace Sudoku;

TEST(BoardValidity, EmptyBoardShouldBeValid) {
  Board board({{0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0}});

  EXPECT_TRUE(board.isValid());
}

TEST(BoardValidity, FullValidBoardShouldBeValid) {
  Board board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
               {4, 5, 6, 7, 8, 9, 1, 2, 3},
               {7, 8, 9, 1, 2, 3, 4, 5, 6},
               {2, 3, 4, 5, 6, 7, 8, 9, 1},
               {5, 6, 7, 8, 9, 1, 2, 3, 4},
               {8, 9, 1, 2, 3, 4, 5, 6, 7},
               {3, 4, 5, 6, 7, 8, 9, 1, 2},
               {6, 7, 8, 9, 1, 2, 3, 4, 5},
               {9, 1, 2, 3, 4, 5, 6, 7, 8}});

  EXPECT_TRUE(board.isValid());
}

TEST(BoardValidity, RepeatedNumbersOnSameLineShouldBeInvalid) {
  Board board({{0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 9, 0, 0, 0, 9},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0}});

  EXPECT_FALSE(board.isValid());
}

TEST(BoardValidity, RepeatedNumbersOnDifferentLinesShouldBeValid) {
  Board board({{0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 9},
               {9, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0}});

  EXPECT_TRUE(board.isValid());
}

TEST(BoardValidity, RepeatedNumbersOnSameColumnShouldBeInvalid) {
  Board board({{0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 9, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 9, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0}});

  EXPECT_FALSE(board.isValid());
}

TEST(BoardValidity, RepeatedNumbersOnDifferentColumnsShouldBeValid) {
  Board board({{0, 0, 0, 0, 0, 9, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 9, 0, 0, 0, 0}});

  EXPECT_TRUE(board.isValid());
}

TEST(BoardValidity, RepeatedNumbersOnSameSquareShouldBeInvalid) {
  Board board({{0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 9, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 9, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0}});

  EXPECT_FALSE(board.isValid());
}
