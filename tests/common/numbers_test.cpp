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
using Puzzles::Numbers::Number;

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

TEST(Numbers_Number, CreateFromString) {
  Number negativeOne("-1");
  Number zero("0");
  Number one("1");

  EXPECT_EQ(std::to_string(negativeOne), "-1");
  EXPECT_EQ(std::to_string(zero), "0");
  EXPECT_EQ(std::to_string(one), "1");
}

TEST(Numbers_Number, CreateFromInt) {
  Number negativeOne(-1);
  Number zero(0);
  Number one(1);

  EXPECT_EQ(std::to_string(negativeOne), "-1");
  EXPECT_EQ(std::to_string(zero), "0");
  EXPECT_EQ(std::to_string(one), "1");
}

TEST(Numbers_Number, Addition) {
  Number one(1);
  Number two(2);
  Number three(3);
  Number five(5);
  Number nine(9);
  Number fifteen(15);
  Number oneHundredTwentyThree(123);
  Number twoHundredThirtyFour(234);
  Number absurdNumberOne("1354645611354413541715318441313195");
  Number absurdNumberTwo("137415147537554114372745478463741");

  Number half(1, 2);
  Number oneOverFiveHundredTwelve(1, 512);

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
  EXPECT_EQ(std::to_string(absurdNumberOne + absurdNumberTwo), "1492060758891967656088063919776936");
  EXPECT_EQ(std::to_string(five + oneOverFiveHundredTwelve), "2561/512");
  EXPECT_EQ(std::to_string(half + half), "1");
}

TEST(Numbers_Number, Comparison_LessThan) {
  EXPECT_TRUE(Number(0) < Number(1));
  EXPECT_TRUE(Number(9) < Number(10));
  EXPECT_TRUE(Number("18446744073709551615") < Number("18446744073709551616"));
  EXPECT_TRUE(Number(-500) < Number(0));
  EXPECT_TRUE(Number(-500) < Number(1));
  EXPECT_TRUE(Number(-500) < Number(-499));

  EXPECT_FALSE(Number(0) < Number(0));
  EXPECT_FALSE(Number(1) < Number(0));
  EXPECT_FALSE(Number(10) < Number(9));
  EXPECT_FALSE(Number("18446744073709551616") < Number("18446744073709551616"));
  EXPECT_FALSE(Number(0) < Number(-500));
  EXPECT_FALSE(Number(1) < Number(-500));
  EXPECT_FALSE(Number(-499) < Number(-500));
  EXPECT_FALSE(Number(-500) < Number(-500));
}
