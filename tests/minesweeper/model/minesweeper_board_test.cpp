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

#include "minesweeper/model/board.h"

#include <gtest/gtest.h>

using namespace Minesweeper;

inline Board trivialBoard() {
  return Board({false, false, false, true}, 2, Move(0, 0));
}

inline Board trivialBoardWithBlanks() {
  return Board({false, false, false, false, false, true}, 2, Move(0, 0));
}

TEST(Board, CountFunctionsShouldWorkOnATrivalOneBombBoard) {
  auto board = trivialBoard();

  EXPECT_EQ(board.cellCount(), 4);
  EXPECT_EQ(board.columnCount(), 2);
  EXPECT_EQ(board.bombCount(), 1);
}

TEST(Board, CountFunctionsShouldWorkOnATrivalRectangularBoardWithBlanks) {
  auto board = trivialBoardWithBlanks();

  EXPECT_EQ(board.cellCount(), 6);
  EXPECT_EQ(board.columnCount(), 3);
  EXPECT_EQ(board.bombCount(), 1);
}

TEST(Board, BoardShouldAddNumberOnes) {
  auto board = trivialBoard();

  EXPECT_EQ(board.cellAt(0), '1');
  EXPECT_EQ(board.cellAt(1), '1');
  EXPECT_EQ(board.cellAt(2), '1');
  EXPECT_EQ(board.cellAt(3), 'B');
}

TEST(Board, BoardShouldAddNumberOnesAndBlanks) {
  auto board = trivialBoardWithBlanks();

  EXPECT_EQ(board.cellAt(0), '0');
  EXPECT_EQ(board.cellAt(1), '1');
  EXPECT_EQ(board.cellAt(2), '1');
  EXPECT_EQ(board.cellAt(3), '0');
  EXPECT_EQ(board.cellAt(4), '1');
  EXPECT_EQ(board.cellAt(5), 'B');
}
