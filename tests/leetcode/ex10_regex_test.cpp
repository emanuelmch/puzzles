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

#define CREATE_TEST_WORKAROUND(string, pattern, name, expected)                                                                   \
  TEST(LeetCode_10, LeetCode_10_##name) { EXPECT_##expected(isMatch(string, pattern)); }
#define CREATE_TEST(string, pattern, name, expected)                                                                   \
  CREATE_TEST_WORKAROUND(string, pattern, name, expected)
#define TEST_FALSE(string, pattern) CREATE_TEST(string, pattern, __LINE__, FALSE)
#define TEST_TRUE(string, pattern) CREATE_TEST(string, pattern, __LINE__, TRUE)

TEST_FALSE("aa", "a")
TEST_TRUE("aa", "aa")
TEST_TRUE("aa", "a*")
TEST_TRUE("ab", ".*")
TEST_TRUE("aab", "c*a*b")
TEST_FALSE("mississippi", "mis*is*p*.")
TEST_FALSE("ab", ".*c")
TEST_TRUE("aaa", "a*a")
TEST_TRUE("aaa", "ab*a*c*a")
TEST_FALSE("b", "b.*c")

TEST_FALSE("a", "aa")
TEST_TRUE("", "a*")
TEST_FALSE("a*bb", "bb")
TEST_TRUE("bb", "a*bb")
TEST_TRUE("aaa", "aa*aa")
TEST_TRUE("aaa", "aa*ab*a")
TEST_TRUE("aaa", "aa*b*aa")
TEST_TRUE("aaa", "a*a*a*a*a*a")
