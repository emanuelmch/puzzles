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

constexpr uintmax_t next(auto it) {
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

TEST(Maths, Sequences_Emirps) {
  auto sequence = Sequences::emirps();
  auto it = sequence.begin();

  EXPECT_EQ(*it, 13);
  EXPECT_EQ(next(it), 17);
  EXPECT_EQ(next(it), 31);
  EXPECT_EQ(next(it), 37);
  EXPECT_EQ(next(it), 71);
  EXPECT_EQ(next(it), 73);
  EXPECT_EQ(next(it), 79);
  EXPECT_EQ(next(it), 97);
  EXPECT_EQ(next(it), 107);
  EXPECT_EQ(next(it), 113);
  EXPECT_EQ(next(it), 149);
  EXPECT_EQ(next(it), 157);
  EXPECT_EQ(next(it), 167);
  EXPECT_EQ(next(it), 179);
  EXPECT_EQ(next(it), 199);
  EXPECT_EQ(next(it), 311);
  EXPECT_EQ(next(it), 337);
  EXPECT_EQ(next(it), 347);
  EXPECT_EQ(next(it), 359);
  EXPECT_EQ(next(it), 389);
  EXPECT_EQ(next(it), 701);
  EXPECT_EQ(next(it), 709);
  EXPECT_EQ(next(it), 733);
  EXPECT_EQ(next(it), 739);
  EXPECT_EQ(next(it), 743);
  EXPECT_EQ(next(it), 751);
  EXPECT_EQ(next(it), 761);
  EXPECT_EQ(next(it), 769);
  EXPECT_EQ(next(it), 907);
  EXPECT_EQ(next(it), 937);
  EXPECT_EQ(next(it), 941);
  EXPECT_EQ(next(it), 953);
  EXPECT_EQ(next(it), 967);
  EXPECT_EQ(next(it), 971);
  EXPECT_EQ(next(it), 983);
  EXPECT_EQ(next(it), 991);
  EXPECT_EQ(next(it), 1009);
  EXPECT_EQ(next(it), 1021);
  EXPECT_EQ(next(it), 1031);
  EXPECT_EQ(next(it), 1033);
  EXPECT_EQ(next(it), 1061);
  EXPECT_EQ(next(it), 1069);
  EXPECT_EQ(next(it), 1091);
  EXPECT_EQ(next(it), 1097);
  EXPECT_EQ(next(it), 1103);
  EXPECT_EQ(next(it), 1109);
  EXPECT_EQ(next(it), 1151);
  EXPECT_EQ(next(it), 1153);
  EXPECT_EQ(next(it), 1181);
  EXPECT_EQ(next(it), 1193);
}

TEST(Maths, Sequences_Primes) {
  auto sequence = Sequences::primes();
  auto it = sequence.begin();

  EXPECT_EQ(*it, 2);
  EXPECT_EQ(next(it), 3);
  EXPECT_EQ(next(it), 5);
  EXPECT_EQ(next(it), 7);
  EXPECT_EQ(next(it), 11);
  EXPECT_EQ(next(it), 13);
  EXPECT_EQ(next(it), 17);
  EXPECT_EQ(next(it), 19);
  EXPECT_EQ(next(it), 23);
  EXPECT_EQ(next(it), 29);
  EXPECT_EQ(next(it), 31);
  EXPECT_EQ(next(it), 37);
}

TEST(Maths, Sequences_PeriodOfDecimalExpansionOfReciprocalOfPrimes) {
  auto sequence = Sequences::periodOfDecimalExpansionOfReciprocalOfPrimes();
  auto it = sequence.begin();

  EXPECT_EQ(*it, 0);       // 1/2 = 0.5
  EXPECT_EQ(next(it), 1);  // 1/3 = 0.3...
  EXPECT_EQ(next(it), 0);  // 1/5 = 0.2
  EXPECT_EQ(next(it), 6);  // 1/7 = 0.14285_7...
  EXPECT_EQ(next(it), 2);  // 1/11 = 0.09...
  EXPECT_EQ(next(it), 6);  // 1/13 = 0.07692_3...
  EXPECT_EQ(next(it), 16); // 1/17 = 0.05882_35294_11764_7...
  EXPECT_EQ(next(it), 18); // 1/19 = 0.05263_15789_47368_421
  EXPECT_EQ(next(it), 22); // 1/23 = 0.04347_82608_69565_21739_13...
  EXPECT_EQ(next(it), 28); // 1/29 = 0.03448_27586_20689_65517_24137_931...
  EXPECT_EQ(next(it), 15); // 1/31 = 0.03225_80645_16129...
  EXPECT_EQ(next(it), 3);  // 1/37 = 0.027...
}

#endif // defined(__cpp_impl_coroutine)
