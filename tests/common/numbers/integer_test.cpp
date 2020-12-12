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
