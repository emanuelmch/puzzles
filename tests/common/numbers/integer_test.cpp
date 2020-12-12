/*
 * Copyright (c) 2020 Emanuel Machado da Silva
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

#include "common/numbers/integer.h"

#include <gtest/gtest.h>

using pzl::Integer;

TEST(Integer, CreateFromString) {
  EXPECT_EQ(std::to_string(Integer{"-1"}), "-1");
  EXPECT_EQ(std::to_string(Integer{"0"}), "0");
  EXPECT_EQ(std::to_string(Integer{"1"}), "1");

  EXPECT_EQ(std::to_string(Integer{"137415147537554114372745478463741"}), "137415147537554114372745478463741");
  EXPECT_EQ(std::to_string(Integer{"1354645611354413541715318441313195"}), "1354645611354413541715318441313195");
}

TEST(Integer, CreateFromInt) {
  EXPECT_EQ(std::to_string(Integer{-1}), "-1");
  EXPECT_EQ(std::to_string(Integer{0}), "0");
  EXPECT_EQ(std::to_string(Integer{1}), "1");
  EXPECT_EQ(std::to_string(Integer{2}), "2");
  EXPECT_EQ(std::to_string(Integer{3}), "3");
  EXPECT_EQ(std::to_string(Integer{4}), "4");
  EXPECT_EQ(std::to_string(Integer{5}), "5");
  EXPECT_EQ(std::to_string(Integer{6}), "6");
  EXPECT_EQ(std::to_string(Integer{7}), "7");
  EXPECT_EQ(std::to_string(Integer{8}), "8");
  EXPECT_EQ(std::to_string(Integer{9}), "9");
  EXPECT_EQ(std::to_string(Integer{10}), "10");
  EXPECT_EQ(std::to_string(Integer{100}), "100");
  EXPECT_EQ(std::to_string(Integer{123}), "123");
  EXPECT_EQ(std::to_string(Integer{456}), "456");
  EXPECT_EQ(std::to_string(Integer{789}), "789");

  constexpr intmax_t max = std::numeric_limits<intmax_t>::max();
  EXPECT_EQ(std::to_string(Integer{max}), std::to_string(max));
}

TEST(Integer, Addition) {
  Integer negativeFive{-5};
  Integer negativeOne{-1};
  Integer zero{0};
  Integer one{1};
  Integer two{2};
  Integer three{3};
  Integer four{4};
  Integer five{5};
  Integer nine{9};
  Integer fifteen{15};
  Integer oneHundredTwentyThree{123};
  Integer twoHundredThirtyFour{234};
  Integer absurdIntegerOne{"1354645611354413541715318441313195"};
  Integer absurdIntegerTwo{"137415147537554114372745478463741"};

  EXPECT_EQ(std::to_string(zero + one), "1");
  EXPECT_EQ(std::to_string(one + zero), "1");
  EXPECT_EQ(std::to_string(one + one), "2");
  EXPECT_EQ(std::to_string(one + two), "3");
  EXPECT_EQ(std::to_string(two + one), "3");
  EXPECT_EQ(std::to_string(one + three), "4");
  EXPECT_EQ(std::to_string(three + one), "4");
  EXPECT_EQ(std::to_string(one + oneHundredTwentyThree), "124");
  EXPECT_EQ(std::to_string(oneHundredTwentyThree + one), "124");
  EXPECT_EQ(std::to_string(oneHundredTwentyThree + twoHundredThirtyFour), "357");
  EXPECT_EQ(std::to_string(twoHundredThirtyFour + oneHundredTwentyThree), "357");
  EXPECT_EQ(std::to_string(five + nine), "14");
  EXPECT_EQ(std::to_string(nine + five), "14");
  EXPECT_EQ(std::to_string(nine + fifteen), "24");
  EXPECT_EQ(std::to_string(fifteen + nine), "24");
  EXPECT_EQ(std::to_string(absurdIntegerOne + zero), "1354645611354413541715318441313195");
  EXPECT_EQ(std::to_string(absurdIntegerOne + absurdIntegerTwo), "1492060758891967656088063919776936");

  EXPECT_EQ(std::to_string(one + negativeFive), "-4");
  EXPECT_EQ(std::to_string(negativeFive + one), "-4");
  EXPECT_EQ(std::to_string(four + negativeOne), "3");
  EXPECT_EQ(std::to_string(negativeOne + four), "3");
  EXPECT_EQ(std::to_string(two + negativeOne), "1");
  EXPECT_EQ(std::to_string(negativeOne + two), "1");
  EXPECT_EQ(std::to_string(negativeOne + negativeOne), "-2");
  EXPECT_EQ(std::to_string(negativeOne + negativeFive), "-6");
  EXPECT_EQ(std::to_string(negativeFive + negativeOne), "-6");
  EXPECT_EQ(std::to_string(negativeOne + zero), "-1");
  EXPECT_EQ(std::to_string(zero + negativeOne), "-1");
}

TEST(Integer, Subtraction) {
  Integer zero{0};
  Integer one{1};
  Integer two{2};
  Integer five{5};
  Integer ten{10};
  Integer hundred{100};

  EXPECT_EQ(std::to_string(zero - zero), "0");
  EXPECT_EQ(std::to_string(one - zero), "1");
  EXPECT_EQ(std::to_string(one - one), "0");
  EXPECT_EQ(std::to_string(two - zero), "2");
  EXPECT_EQ(std::to_string(two - one), "1");
  EXPECT_EQ(std::to_string(two - two), "0");
  EXPECT_EQ(std::to_string(ten - one), "9");
  EXPECT_EQ(std::to_string(hundred - one), "99");
  EXPECT_EQ(std::to_string(hundred - ten), "90");

  EXPECT_EQ(std::to_string(zero - one), "-1");
  EXPECT_EQ(std::to_string(zero - five), "-5");
  EXPECT_EQ(std::to_string(one - five), "-4");
}

TEST(Integer, Comparison_EqualTo) {
  EXPECT_TRUE(Integer{-1} == Integer{-1});
  EXPECT_TRUE(Integer{0} == Integer{0});
  EXPECT_TRUE(Integer{1} == Integer{1});

  EXPECT_FALSE(Integer{-1} == Integer{0});
  EXPECT_FALSE(Integer{-1} == Integer{1});
  EXPECT_FALSE(Integer{0} == Integer{-1});
  EXPECT_FALSE(Integer{0} == Integer{1});
  EXPECT_FALSE(Integer{1} == Integer{-1});
  EXPECT_FALSE(Integer{1} == Integer{0});
}
