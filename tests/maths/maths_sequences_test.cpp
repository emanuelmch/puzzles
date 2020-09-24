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

#include "maths/sequences.h"

#if __has_include(<version>)
#include <version>
#endif

#if defined(__cpp_impl_coroutine)

#include <gtest/gtest.h>

using namespace Maths;

constexpr int next(auto it) {
  return **(++it);
}

TEST(Maths, Sequences_HighlyCompositeNumbers) {
  auto sequence = Sequences::highlyCompositeNumbers();
  auto it = sequence.begin();

  EXPECT_EQ(*it, 1);
  EXPECT_EQ(next(it), 2);
  EXPECT_EQ(next(it), 4);
  EXPECT_EQ(next(it), 6);
  EXPECT_EQ(next(it), 12);
  EXPECT_EQ(next(it), 24);
  EXPECT_EQ(next(it), 36);
  EXPECT_EQ(next(it), 48);
  EXPECT_EQ(next(it), 60);
  EXPECT_EQ(next(it), 120);
  EXPECT_EQ(next(it), 180);
  EXPECT_EQ(next(it), 240);
  EXPECT_EQ(next(it), 360);
  EXPECT_EQ(next(it), 720);
  EXPECT_EQ(next(it), 840);
  EXPECT_EQ(next(it), 1260);
  EXPECT_EQ(next(it), 1680);
  EXPECT_EQ(next(it), 2520);
  EXPECT_EQ(next(it), 5040);
  EXPECT_EQ(next(it), 7560);
}

#endif // defined(__cpp_impl_coroutine)
