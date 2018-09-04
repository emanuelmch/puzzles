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

TEST(Board, ShouldInitWithBlankSpaces) {
  Board board = BoardBuilder().column({1, 0})
                            ->column({0, 1})
                            ->row({1, 0})
                            ->row({0, 1})
                            ->build();

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

//FIXME: Tests for  uint blankCellsOnColumn(unsigned int);
//FIXME: Tests for  vector<uint> missingColorsOnColumn(uint);
