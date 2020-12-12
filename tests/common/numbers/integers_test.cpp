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

#include "common/numbers/integers.h"

#include <gtest/gtest.h>

using namespace pzl;

TEST(Numbers, GreatestCommonDivisor) {
  EXPECT_EQ(greatestCommonDivisor(Integer{1}, Integer{3}), 1);
  EXPECT_EQ(greatestCommonDivisor(Integer{17}, Integer{19}), Integer{1});
  EXPECT_EQ(greatestCommonDivisor(Integer{10}, Integer{25}), Integer{5});
  EXPECT_EQ(greatestCommonDivisor(Integer{3154}, Integer{4522}), Integer{38});
}

TEST(Numbers, LowestCommonMultiple) {
  EXPECT_EQ(lowestCommonMultiple(Integer{1}, Integer{30}), Integer{30});
  EXPECT_EQ(lowestCommonMultiple(Integer{10}, Integer{25}), Integer{50});
}
