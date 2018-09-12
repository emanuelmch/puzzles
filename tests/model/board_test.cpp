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
  return BoardBuilder(2).column({1, 1})
          ->column({1, 1})
          ->row({1, 1})
          ->row({1, 1})
          ->build();
}

inline Board createSquareBoardWithVerticalLines() {
  return BoardBuilder(2).column({2, 0}, {true})
          ->column({0, 2}, {false, true})
          ->row({1, 1})
          ->row({1, 1})
          ->build();
}

inline Board createSquareBoardWithHorizontalLines() {
  return BoardBuilder(2).column({1, 1})
          ->column({1, 1})
          ->row({2, 0}, {true})
          ->row({0, 2}, {false, true})
          ->build();
}

inline Board createNonContiguousRectangularBoard() {
  return BoardBuilder(2).column({2, 1})
          ->column({1, 2})
          ->row({1, 1})
          ->row({1, 1})
          ->row({1, 1})
          ->build();
}

inline Board createContiguousRectangularBoard() {
  return BoardBuilder(2).column({2, 1}, {true})
          ->column({1, 2}, {false, true})
          ->row({1, 1})
          ->row({1, 1})
          ->row({1, 1})
          ->build();
}

inline Board createSquareBoard() {
  return createSquareBoardWithDiagonals();
}

inline Board createRectangularBoard() {
  return createNonContiguousRectangularBoard();
}

TEST(Board, ShouldWorkWithRectangularBoards) {
  Board board = createRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  ASSERT_EQ(state.size(), 2);
  ASSERT_EQ(state[0].size(), 3);
  ASSERT_EQ(state[1].size(), 3);

  EXPECT_EQ(state[0][0], Blank);
  EXPECT_EQ(state[0][1], Blank);
  EXPECT_EQ(state[0][2], Blank);
  EXPECT_EQ(state[1][0], Blank);
  EXPECT_EQ(state[1][1], Blank);
  EXPECT_EQ(state[1][2], Blank);
}

TEST(Board, ShouldBeValidWhenEmpty) {
  Board board = createSquareBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeValidWhenDiagonalsAreFilledCorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[1][0] = C1;
  state[1][1] = C0;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeValidWhenDiagonalsArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[1][1] = C0;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeInvalidWhenDiagonalsAreFilledIncorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;
  state[1][0] = C0;
  state[1][1] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenDiagonalsArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;
  state[1][1] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeValidWhenVerticalLinesAreFilledCorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;
  state[1][0] = C1;
  state[1][1] = C1;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeValidWhenVerticalLinesArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;
  state[1][1] = C1;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeInvalidWhenVerticalLinesAreFilledIncorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[1][0] = C0;
  state[1][1] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenVerticalLinesArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[1][1] = C1;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeValidWhenHorizontalLinesAreFilledCorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[1][0] = C0;
  state[1][1] = C1;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeValidWhenHorizontalLinesArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[1][1] = C1;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeInvalidWhenHorizontalLinesAreFilledIncorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[1][0] = C0;
  state[1][1] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenHorizontalLinesArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;
  state[1][1] = C1;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeValidWhenNonContiguousRectangularBoardIsFilledCorrectly) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[0][2] = C0;
  state[1][0] = C1;
  state[1][1] = C0;
  state[1][2] = C1;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsFilledWithIncorrectAmounts) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[0][2] = C1;
  state[1][0] = C1;
  state[1][1] = C0;
  state[1][2] = C1;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsFilledInInvalidPlaces) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;
  state[0][2] = C1;
  state[1][0] = C1;
  state[1][1] = C1;
  state[1][2] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsPartiallyFilledWithIncorrectAmounts) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][1] = C1;
  state[1][1] = C1;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsPartiallyFilledInInvalidPlaces) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeValidWhenContiguousRectangularBoardIsFilledCorrectly) {
  Board board = createContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C0;
  state[0][2] = C1;
  state[1][0] = C1;
  state[1][1] = C1;
  state[1][2] = C0;

  ASSERT_EQ(board.isValid(&state), true);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsFilledWithIncorrectAmounts) {
  Board board = createContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[0][2] = C1;
  state[1][0] = C1;
  state[1][1] = C1;
  state[1][2] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsFilledInInvalidPlaces) {
  Board board = createContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][1] = C1;
  state[0][2] = C0;
  state[1][0] = C1;
  state[1][1] = C0;
  state[1][2] = C1;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsPartiallyFilledWithIncorrectAmounts) {
  Board board = createContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C1;
  state[0][1] = C1;

  ASSERT_EQ(board.isValid(&state), false);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsPartiallyFilledInInvalidPlaces) {
  Board board = createContiguousRectangularBoard();
  BoardState state = emptyBoardState(board.columnCount, board.rowCount);

  state[0][0] = C0;
  state[0][2] = C0;

  ASSERT_EQ(board.isValid(&state), false);
}

//TODO: Tests for  ushort countColorIn{Column,Row}
//TODO: Tests for  ushort clueFor{Column,Row}
