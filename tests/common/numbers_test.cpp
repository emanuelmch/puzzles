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

#include "common/numbers.h"

#include <gtest/gtest.h>

using namespace Puzzles::Numbers;

TEST(Numbers, CharToInt) {
  EXPECT_EQ(ctoi('0'), 0);
  EXPECT_EQ(ctoi('1'), 1);
  EXPECT_EQ(ctoi('2'), 2);
  EXPECT_EQ(ctoi('3'), 3);
  EXPECT_EQ(ctoi('4'), 4);
  EXPECT_EQ(ctoi('5'), 5);
  EXPECT_EQ(ctoi('6'), 6);
  EXPECT_EQ(ctoi('7'), 7);
  EXPECT_EQ(ctoi('8'), 8);
  EXPECT_EQ(ctoi('9'), 9);
}

TEST(Numbers, IntToChar) {
  EXPECT_EQ(itoc(0), '0');
  EXPECT_EQ(itoc(1), '1');
  EXPECT_EQ(itoc(2), '2');
  EXPECT_EQ(itoc(3), '3');
  EXPECT_EQ(itoc(4), '4');
  EXPECT_EQ(itoc(5), '5');
  EXPECT_EQ(itoc(6), '6');
  EXPECT_EQ(itoc(7), '7');
  EXPECT_EQ(itoc(8), '8');
  EXPECT_EQ(itoc(9), '9');
}

TEST(Numbers, Factorial) {
  EXPECT_EQ(factorial(0), 1);
  EXPECT_EQ(factorial(1), 1);
  EXPECT_EQ(factorial(2), 2);
  EXPECT_EQ(factorial(12), 479001600);
}

TEST(Numbers, GreatestCommonDivisor) {
  EXPECT_EQ(greatestCommonDivisor(1, 3), 1);
  EXPECT_EQ(greatestCommonDivisor(17, 19), 1);
  EXPECT_EQ(greatestCommonDivisor(10, 25), 5);
  EXPECT_EQ(greatestCommonDivisor(3154, 4522), 38);
}

TEST(Numbers, LowestCommonMultiple) {
  EXPECT_EQ(lowestCommonMultiple(1, 30), 30);
  EXPECT_EQ(lowestCommonMultiple(10, 25), 50);
}
