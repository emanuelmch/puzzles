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

#include "leetcode/ex8_atoi.h"

#include <gtest/gtest.h>

using namespace Puzzles::LeetCode;

using std::make_tuple;
using std::string;
using std::tuple;
using ::testing::TestWithParam;
using ::testing::Values;

typedef int (*AtoiFunction)(const string &);

TEST(LeetCode, LeetCode_8) {
  AtoiFunction atois[] = {myAtoi_firstAttempt, myAtoi_refined, myAtoi_cretino};
  for (auto i = 0; i < 3; ++i) {
    auto myAtoi = atois[i];

    EXPECT_EQ(myAtoi(""), 0) << "Using function #" << i;
    EXPECT_EQ(myAtoi("   "), 0) << "Using function #" << i;
    EXPECT_EQ(myAtoi("42"), 42) << "Using function #" << i;
    EXPECT_EQ(myAtoi("  -42"), -42) << "Using function #" << i;
    EXPECT_EQ(myAtoi("4193 with words"), 4193) << "Using function #" << i;
    EXPECT_EQ(myAtoi("words and 987"), 0) << "Using function #" << i;
    EXPECT_EQ(myAtoi("2147483648"), 2147483647) << "Using function #" << i;
    EXPECT_EQ(myAtoi("-1089159117"), -1089159117) << "Using function #" << i;
    EXPECT_EQ(myAtoi("-2147483648"), -2147483648) << "Using function #" << i;
    EXPECT_EQ(myAtoi("-91283472332"), -2147483648) << "Using function #" << i;
    EXPECT_EQ(myAtoi("20000000000000000000"), 2147483647) << "Using function #" << i;
    EXPECT_EQ(myAtoi("  0000000000012345678"), 12345678) << "Using function #" << i;
    EXPECT_EQ(myAtoi("+-2"), 0) << "Using function #" << i;
  }
}

TEST(LeetCode, CountDigits) {
  EXPECT_EQ(countDigits(7), 1);
  EXPECT_EQ(countDigits(47), 2);
  EXPECT_EQ(countDigits(647), 3);
  EXPECT_EQ(countDigits(3647), 4);
  EXPECT_EQ(countDigits(83647), 5);
  EXPECT_EQ(countDigits(483647), 6);
  EXPECT_EQ(countDigits(7483647), 7);
  EXPECT_EQ(countDigits(47483647), 8);
  EXPECT_EQ(countDigits(147483647), 9);
  EXPECT_EQ(countDigits(2147483647), 10);
}
