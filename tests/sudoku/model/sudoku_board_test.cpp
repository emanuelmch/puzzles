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

inline Board emptyBoard() {
  return Board({{0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0}});
}

inline Board fullBoard() {
  return Board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                {4, 5, 6, 7, 8, 9, 1, 2, 3},
                {7, 8, 9, 1, 2, 3, 4, 5, 6},
                {2, 3, 4, 5, 6, 7, 8, 9, 1},
                {5, 6, 7, 8, 9, 1, 2, 3, 4},
                {8, 9, 1, 2, 3, 4, 5, 6, 7},
                {3, 4, 5, 6, 7, 8, 9, 1, 2},
                {6, 7, 8, 9, 1, 2, 3, 4, 5},
                {9, 1, 2, 3, 4, 5, 6, 7, 8}});
}

TEST(Board, FirstEmptyCellShouldReturnZeroOnEmptyCells) {
  auto board = emptyBoard();

  EXPECT_EQ(board.firstEmptyCell(), 0);
}

TEST(Board, FirstEmptyCellShouldReturnOneWhenFirstCellIsTaken) {
  Board board({{9, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0}});

  EXPECT_EQ(board.firstEmptyCell(), 1);
}

TEST(Board, FirstEmptyCellShouldWorkWhenOnlyLastCellIsEmpty) {
  Board board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
               {4, 5, 6, 7, 8, 9, 1, 2, 3},
               {7, 8, 9, 1, 2, 3, 4, 5, 6},
               {2, 3, 4, 5, 6, 7, 8, 9, 1},
               {5, 6, 7, 8, 9, 1, 2, 3, 4},
               {8, 9, 1, 2, 3, 4, 5, 6, 7},
               {3, 4, 5, 6, 7, 8, 9, 1, 2},
               {6, 7, 8, 9, 1, 2, 3, 4, 5},
               {9, 1, 2, 3, 4, 5, 6, 7, 0}});

  EXPECT_EQ(board.firstEmptyCell(), 80);
}

TEST(Board, FirstEmptyCellShouldReturnAnInvalidValueWhenBoardIsFull) {
  auto board = fullBoard();

  EXPECT_GT(board.firstEmptyCell(), 80);
}

TEST(Board, TwoEmptyBoardsShouldBeEqual) {
  auto board0 = emptyBoard();
  auto board1 = emptyBoard();

  EXPECT_EQ(board0, board1);
}

TEST(Board, TwoFullBoardsShouldBeEqual) {
  auto board0 = fullBoard();
  auto board1 = fullBoard();

  EXPECT_EQ(board0, board1);
}

TEST(Board, EmptyAndFullBoardsShouldNotBeEqual) {
  auto empty = emptyBoard();
  auto full = fullBoard();

  EXPECT_NE(empty, full);
}
