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

#include "cpic/model/board_builder.h"

#include "cpic/model/board_state.h"

#include <gtest/gtest.h>

using namespace CPic;

inline Board createSquareBoardWithDiagonals() {
  return BoardBuilder(2) //
      .column({1, 1})
      ->column({1, 1})
      ->row({1, 1})
      ->row({1, 1})
      ->build();
}

inline Board createSquareBoardWithVerticalLines() {
  return BoardBuilder(2) //
      .column({2, 0}, {true})
      ->column({0, 2}, {false, true})
      ->row({1, 1})
      ->row({1, 1})
      ->build();
}

inline Board createSquareBoardWithHorizontalLines() {
  return BoardBuilder(2) //
      .column({1, 1})
      ->column({1, 1})
      ->row({2, 0}, {true})
      ->row({0, 2}, {false, true})
      ->build();
}

inline Board createNonContiguousRectangularBoard() {
  return BoardBuilder(2) //
      .column({2, 1})
      ->column({1, 2})
      ->row({1, 1})
      ->row({1, 1})
      ->row({1, 1})
      ->build();
}

inline Board createContiguousRectangularBoard() {
  return BoardBuilder(2)
      .column({2, 1}, {true})
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
  BoardState state = BoardState(board.columnCount, board.rowCount);

  ASSERT_EQ(state.columnCount(), 2);
  ASSERT_EQ(state.rowCount(), 3);

  EXPECT_EQ(state.colorAt(0, 0), Blank);
  EXPECT_EQ(state.colorAt(0, 1), Blank);
  EXPECT_EQ(state.colorAt(0, 2), Blank);
  EXPECT_EQ(state.colorAt(1, 0), Blank);
  EXPECT_EQ(state.colorAt(1, 1), Blank);
  EXPECT_EQ(state.colorAt(1, 2), Blank);
}

TEST(Board, ShouldBeValidWhenEmpty) {
  Board board = createSquareBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeValidWhenDiagonalsAreFilledCorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C0);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeValidWhenDiagonalsArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 1, C0);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeInvalidWhenDiagonalsAreFilledIncorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);
  state.setColorAt(1, 0, C0);
  state.setColorAt(1, 1, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenDiagonalsArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithDiagonals();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);
  state.setColorAt(1, 1, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeValidWhenVerticalLinesAreFilledCorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C1);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeValidWhenVerticalLinesArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);
  state.setColorAt(1, 1, C1);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeInvalidWhenVerticalLinesAreFilledIncorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 0, C0);
  state.setColorAt(1, 1, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenVerticalLinesArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithVerticalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 1, C1);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeValidWhenHorizontalLinesAreFilledCorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 0, C0);
  state.setColorAt(1, 1, C1);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeValidWhenHorizontalLinesArePartiallyFilledCorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 1, C1);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeInvalidWhenHorizontalLinesAreFilledIncorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 0, C0);
  state.setColorAt(1, 1, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenHorizontalLinesArePartiallyFilledIncorrectly) {
  Board board = createSquareBoardWithHorizontalLines();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);
  state.setColorAt(1, 1, C1);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeValidWhenNonContiguousRectangularBoardIsFilledCorrectly) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(0, 2, C0);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C0);
  state.setColorAt(1, 2, C1);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsFilledWithIncorrectAmounts) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(0, 2, C1);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C0);
  state.setColorAt(1, 2, C1);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsFilledInInvalidPlaces) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);
  state.setColorAt(0, 2, C1);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C1);
  state.setColorAt(1, 2, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsPartiallyFilledWithIncorrectAmounts) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 1, C1);
  state.setColorAt(1, 1, C1);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenNonContiguousRectangularBoardIsPartiallyFilledInInvalidPlaces) {
  Board board = createNonContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeValidWhenContiguousRectangularBoardIsFilledCorrectly) {
  Board board = createContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C0);
  state.setColorAt(0, 2, C1);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C1);
  state.setColorAt(1, 2, C0);

  ASSERT_EQ(state.isValid(&board), true);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsFilledWithIncorrectAmounts) {
  Board board = createContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(0, 2, C1);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C1);
  state.setColorAt(1, 2, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsFilledInInvalidPlaces) {
  Board board = createContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 1, C1);
  state.setColorAt(0, 2, C0);
  state.setColorAt(1, 0, C1);
  state.setColorAt(1, 1, C0);
  state.setColorAt(1, 2, C1);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsPartiallyFilledWithIncorrectAmounts) {
  Board board = createContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C1);
  state.setColorAt(0, 1, C1);

  ASSERT_EQ(state.isValid(&board), false);
}

TEST(Board, ShouldBeInvalidWhenContiguousRectangularBoardIsPartiallyFilledInInvalidPlaces) {
  Board board = createContiguousRectangularBoard();
  BoardState state = BoardState(board.columnCount, board.rowCount);

  state.setColorAt(0, 0, C0);
  state.setColorAt(0, 2, C0);

  ASSERT_EQ(state.isValid(&board), false);
}

// TODO: Tests for Clue clueFor{Column,Row}
// TODO: Tests for uint8_t countPossibilitiesForRow
// TODO: Tests for bool isPossibility
