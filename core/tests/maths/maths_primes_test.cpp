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

#include "maths/primes.h"

#include "compat/set.h"

#include <gtest/gtest.h>

using namespace Maths;

TEST(Maths, IsPrime) {
  compat::set<uint_fast8_t> primes = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                                      43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
  for (auto i = 1u; i <= 100; ++i) {
    if (primes.contains(i)) {
      EXPECT_TRUE(isPrime(i)) << "Prime number " << i << " was reported as NOT being prime";
    } else {
      EXPECT_FALSE(isPrime(i)) << "NON prime number " << i << " was reported as being prime";
    }
  }
}

TEST(Maths, LargestPrimeFactor) {
  EXPECT_EQ(largestPrimeFactor(2), 2);
  EXPECT_EQ(largestPrimeFactor(3), 3);
  EXPECT_EQ(largestPrimeFactor(4), 2);
  EXPECT_EQ(largestPrimeFactor(5), 5);
  EXPECT_EQ(largestPrimeFactor(6), 3);
  EXPECT_EQ(largestPrimeFactor(13195), 29);
}
