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

// FIXME: Should differentiate between contiguous and non-contiguous colors

inline Board createSquareBoardWithDiagonals() {
  return BoardBuilder().column({1, 1})
                      ->column({1, 1})
                      ->row({1, 1})
                      ->row({1, 1})
                      ->build();
}

inline Board createSquareBoardWithVerticalLines() {
  return BoardBuilder().column({2, 0})
                      ->column({0, 2})
                      ->row({1, 1})
                      ->row({1, 1})
                      ->build();
}

inline Board createSquareBoardWithHorizontalLines() {
  return BoardBuilder().column({1, 1})
                      ->column({1, 1})
                      ->row({2, 0})
                      ->row({0, 2})
                      ->build();
}

inline Board createSquareBoard() {
  return createSquareBoardWithDiagonals();
}

TEST(Board, ShouldInitWithBlankSpaces) {
  Board board = createSquareBoard();

  auto results = board.results;
  ASSERT_EQ(2, results.size());
  ASSERT_EQ(2, results[0].size());
  ASSERT_EQ(2, results[1].size());

  EXPECT_EQ(-1, results[0][0]);
  EXPECT_EQ(-1, results[0][1]);
  EXPECT_EQ(-1, results[1][0]);
  EXPECT_EQ(-1, results[1][1]);
}

//FIXME: ShouldWorkWithRectangularBoards

TEST(Board, ShouldBeValidWhenEmpty) {
  Board board = createSquareBoard();

  ASSERT_EQ(true, board.isValid());
}

TEST(Board, ShouldBeValidWhenDiagonalsAreFilledCorrectly) {
  Board board = createSquareBoardWithDiagonals();

  board.results[0][0] = 0;
  board.results[0][1] = 1;
  board.results[1][0] = 1;
  board.results[1][1] = 0;

  ASSERT_EQ(true, board.isValid());
}

TEST(Board, ShouldBeValidWhenDiagonalsArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithDiagonals();

  board.results[0][0] = 0;
  board.results[0][1] = 1;
  board.results[1][1] = 0;

  ASSERT_EQ(true, board.isValid());
}

TEST(Board, ShouldBeInvalidWhenDiagonalsAreFilledIncorrectly) {
  Board board = createSquareBoardWithDiagonals();

  board.results[0][0] = 0;
  board.results[0][1] = 0;
  board.results[1][0] = 0;
  board.results[1][1] = 0;

  ASSERT_EQ(false, board.isValid());
}

TEST(Board, ShouldBeInvalidWhenDiagonalsArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithDiagonals();

  board.results[0][0] = 0;
  board.results[0][1] = 0;
  board.results[1][1] = 0;

  ASSERT_EQ(false, board.isValid());
}

TEST(Board, ShouldBeValidWhenVerticalLinesAreFilledCorrectly) {
  Board board = createSquareBoardWithVerticalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 0;
  board.results[1][0] = 1;
  board.results[1][1] = 1;

  ASSERT_EQ(true, board.isValid());
}

TEST(Board, ShouldBeValidWhenVerticalLinesArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithVerticalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 0;
  board.results[1][1] = 1;

  ASSERT_EQ(true, board.isValid());
}

TEST(Board, ShouldBeInvalidWhenVerticalLinesAreFilledIncorrectly) {
  Board board = createSquareBoardWithVerticalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 1;
  board.results[1][0] = 0;
  board.results[1][1] = 0;

  ASSERT_EQ(false, board.isValid());
}

TEST(Board, ShouldBeInvalidWhenVerticalLinesArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithVerticalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 1;
  board.results[1][1] = 1;

  ASSERT_EQ(false, board.isValid());
}

TEST(Board, ShouldBeValidWhenHorizontalLinesAreFilledCorrectly) {
  Board board = createSquareBoardWithHorizontalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 1;
  board.results[1][0] = 0;
  board.results[1][1] = 1;

  ASSERT_EQ(true, board.isValid());
}

TEST(Board, ShouldBeValidWhenHorizontalLinesArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithHorizontalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 1;
  board.results[1][1] = 1;

  ASSERT_EQ(true, board.isValid());
}

TEST(Board, ShouldBeInvalidWhenHorizontalLinesAreFilledIncorrectly) {
  Board board = createSquareBoardWithHorizontalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 1;
  board.results[1][0] = 0;
  board.results[1][1] = 0;

  ASSERT_EQ(false, board.isValid());
}

TEST(Board, ShouldBeInvalidWhenHorizontalLinesArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithHorizontalLines();

  board.results[0][0] = 0;
  board.results[0][1] = 0;
  board.results[1][1] = 1;

  ASSERT_EQ(false, board.isValid());
}

//FIXME: Tests for  uint blankCellsOnColumn(unsigned int);
//FIXME: Tests for  vector<uint> missingColorsOnColumn(uint);
