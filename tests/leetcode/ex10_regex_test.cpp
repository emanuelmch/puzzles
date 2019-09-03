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

#include "leetcode/ex10_regex.h"

#include <gtest/gtest.h>

using namespace Puzzles::LeetCode;

TEST(LeetCode, LeetCode_10) {
  EXPECT_FALSE(isMatch("aa", "a"));
  EXPECT_TRUE(isMatch("aa", "a."));
  EXPECT_TRUE(isMatch("aa", "a*"));
  EXPECT_TRUE(isMatch("ab", ".*"));
  EXPECT_TRUE(isMatch("aab", "c*a*b"));
  EXPECT_FALSE(isMatch("mississippi", "mis*is*p*."));
  EXPECT_FALSE(isMatch("ab", ".*c"));
  EXPECT_TRUE(isMatch("aaa", "a*a"));
  EXPECT_TRUE(isMatch("aaa", "ab*a*c*a"));
  EXPECT_FALSE(isMatch("b", "b.*c"));

  EXPECT_FALSE(isMatch("a", "aa"));
  EXPECT_TRUE(isMatch("", "a*"));
  EXPECT_FALSE(isMatch("a*bb", "bb"));
  EXPECT_TRUE(isMatch("bb", "a*bb"));
  EXPECT_TRUE(isMatch("aaa", "aa*aa"));
  EXPECT_TRUE(isMatch("aaa", "aa*ab*a"));
  EXPECT_TRUE(isMatch("aaa", "aa*b*aa"));
  EXPECT_TRUE(isMatch("aaa", "a*a*a*a*a*a"));
}
