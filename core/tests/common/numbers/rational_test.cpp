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

#include "common/numbers/rational.h"

#include <gtest/gtest.h>

using pzl::Rational;

TEST(Numbers_Rational, CreateFromString) {
  Rational negativeOne("-1");
  Rational zero("0");
  Rational one("1");

  EXPECT_EQ(std::to_string(negativeOne), "-1");
  EXPECT_EQ(std::to_string(zero), "0");
  EXPECT_EQ(std::to_string(one), "1");
}

TEST(Numbers_Rational, CreateFromInt) {
  EXPECT_EQ(std::to_string(Rational(-2)), "-2");
  EXPECT_EQ(std::to_string(Rational(-1)), "-1");
  EXPECT_EQ(std::to_string(Rational(0)), "0");
  EXPECT_EQ(std::to_string(Rational(1)), "1");
}

TEST(Numbers_Rational, Addition) {
  Rational negativeFive(-5);
  Rational negativeOne(-1);
  Rational zero(0);
  Rational one(1);
  Rational two(2);
  Rational three(3);
  Rational four(4);
  Rational five(5);
  Rational nine(9);
  Rational fifteen(15);
  Rational sixty(60);
  Rational oneHundredTwentyThree(123);
  Rational twoHundredThirtyFour(234);
  Rational absurdNumberOne("1354645611354413541715318441313195");
  Rational absurdNumberTwo("137415147537554114372745478463741");
  Rational absurdNumberThree(-325, 2);

  Rational half(1, 2);
  Rational oneOverFiveHundredTwelve(1, 512);
  Rational negativeOneOverFiveHundredTwelve(-1, 512);

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
  EXPECT_EQ(std::to_string(absurdNumberOne + absurdNumberTwo), "1492060758891967656088063919776936");
  EXPECT_EQ(std::to_string(absurdNumberOne + zero), "1354645611354413541715318441313195");
  EXPECT_EQ(std::to_string(sixty + absurdNumberThree), "-205/2");

  EXPECT_EQ(std::to_string(five + oneOverFiveHundredTwelve), "2561/512");
  EXPECT_EQ(std::to_string(oneOverFiveHundredTwelve + five), "2561/512");
  EXPECT_EQ(std::to_string(five + negativeOneOverFiveHundredTwelve), "2559/512");
  EXPECT_EQ(std::to_string(negativeOneOverFiveHundredTwelve + five), "2559/512");
  EXPECT_EQ(std::to_string(half + half), "1");
  EXPECT_EQ(std::to_string(half + zero), "1/2");

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

TEST(Numbers_Rational, Subtraction) {
  Rational zero(0);
  Rational one(1);
  Rational two(2);
  Rational five(5);
  Rational ten(10);
  Rational hundred(100);

  Rational absurdNumberOne(1537, 512);
  Rational absurdNumberTwo(1, 8192);

  Rational oneOverTwo(1, 2);
  Rational threeOverTwo(3, 2);

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

  EXPECT_EQ(std::to_string(threeOverTwo - oneOverTwo), "1");
  EXPECT_EQ(std::to_string(absurdNumberOne - absurdNumberTwo), "24591/8192");
}

TEST(Numbers_Rational, Multiplication) {
  Rational negativeFour(-4);
  Rational negativeOne(-1);
  Rational zero(0);
  Rational one(1);
  Rational two(2);
  Rational four(4);
  Rational bigNumber("18446744073709551616");
  Rational absurdNumberOne(15630, 6), absurdNumberTwo(5361, 15);

  EXPECT_EQ(std::to_string(zero * zero), "0");
  EXPECT_EQ(std::to_string(zero * one), "0");
  EXPECT_EQ(std::to_string(one * zero), "0");
  EXPECT_EQ(std::to_string(one * one), "1");
  EXPECT_EQ(std::to_string(one * two), "2");
  EXPECT_EQ(std::to_string(two * one), "2");
  EXPECT_EQ(std::to_string(two * four), "8");
  EXPECT_EQ(std::to_string(four * two), "8");
  EXPECT_EQ(std::to_string(bigNumber * zero), "0");
  EXPECT_EQ(std::to_string(zero * bigNumber), "0");
  EXPECT_EQ(std::to_string(bigNumber * one), "18446744073709551616");
  EXPECT_EQ(std::to_string(one * bigNumber), "18446744073709551616");
  EXPECT_EQ(std::to_string(two * bigNumber), "36893488147419103232");

  EXPECT_EQ(std::to_string(zero * negativeOne), "0");

  EXPECT_EQ(std::to_string(negativeFour * negativeOne), "4");
  EXPECT_EQ(std::to_string(negativeOne * negativeFour), "4");
  EXPECT_EQ(std::to_string(negativeFour * one), "-4");
  EXPECT_EQ(std::to_string(one * negativeFour), "-4");
  EXPECT_EQ(std::to_string(negativeFour * two), "-8");
  EXPECT_EQ(std::to_string(two * negativeFour), "-8");
  EXPECT_EQ(std::to_string(negativeOne * one), "-1");
  EXPECT_EQ(std::to_string(one * negativeOne), "-1");
  EXPECT_EQ(std::to_string(negativeOne * two), "-2");
  EXPECT_EQ(std::to_string(two * negativeOne), "-2");

  EXPECT_EQ(std::to_string(absurdNumberOne * absurdNumberTwo), "931027");
}

TEST(Numbers_Rational, Division) {
  Rational minusThreeTwentyFive(-325);
  Rational minusTwo(-2);
  Rational one(1);
  Rational two(2);
  Rational five(5);
  Rational ten(10);
  Rational sixteen(16);
  Rational fifty(50);
  Rational thousandTwentyFour(1024);
  Rational bigNumber(8192);

  EXPECT_EQ(std::to_string(two / one), "2");
  EXPECT_EQ(std::to_string(two / two), "1");
  EXPECT_EQ(std::to_string(ten / two), "5");
  EXPECT_EQ(std::to_string(fifty / two), "25");
  EXPECT_EQ(std::to_string(fifty / ten), "5");
  EXPECT_EQ(std::to_string(thousandTwentyFour / sixteen), "64");
  EXPECT_EQ(std::to_string(bigNumber / sixteen), "512");

  EXPECT_EQ(std::to_string(one / minusTwo), "-1/2");
  EXPECT_EQ(std::to_string(two / minusTwo), "-1");
  EXPECT_EQ(std::to_string(minusTwo / minusTwo), "1");

  EXPECT_EQ(std::to_string(five / two), "5/2");
  EXPECT_EQ(std::to_string(one / bigNumber), "1/8192");
  EXPECT_EQ(std::to_string(minusThreeTwentyFive / two), "-325/2");
}

TEST(Numbers_Rational, Power) {
  Rational negativeFour(-4);
  Rational negativeOne(-1);
  Rational zero(0);
  Rational one(1);
  Rational two(2);
  Rational three(3);
  Rational eight(8);

  EXPECT_EQ(std::to_string(std::pow(one, one)), "1");
  EXPECT_EQ(std::to_string(std::pow(one, zero)), "1");
  EXPECT_EQ(std::to_string(std::pow(one, eight)), "1");
  EXPECT_EQ(std::to_string(std::pow(two, one)), "2");
  EXPECT_EQ(std::to_string(std::pow(two, two)), "4");
  EXPECT_EQ(std::to_string(std::pow(two, eight)), "256");
  EXPECT_EQ(std::to_string(std::pow(eight, zero)), "1");
  EXPECT_EQ(std::to_string(std::pow(zero, eight)), "0");

  EXPECT_EQ(std::to_string(std::pow(negativeOne, one)), "-1");
  EXPECT_EQ(std::to_string(std::pow(negativeOne, two)), "1");
  EXPECT_EQ(std::to_string(std::pow(negativeFour, one)), "-4");
  EXPECT_EQ(std::to_string(std::pow(negativeFour, two)), "16");
  EXPECT_EQ(std::to_string(std::pow(negativeFour, three)), "-64");
}

TEST(Numbers_Rational, Comparison_LessThan) {
  EXPECT_TRUE(Rational(0) < Rational(1));
  EXPECT_TRUE(Rational(9) < Rational(10));
  EXPECT_TRUE(Rational("18446744073709551615") < Rational("18446744073709551616"));
  EXPECT_TRUE(Rational(-500) < Rational(0));
  EXPECT_TRUE(Rational(-500) < Rational(1));
  EXPECT_TRUE(Rational(-500) < Rational(-499));

  EXPECT_FALSE(Rational(0) < Rational(0));
  EXPECT_FALSE(Rational(1) < Rational(0));
  EXPECT_FALSE(Rational(10) < Rational(9));
  EXPECT_FALSE(Rational("18446744073709551616") < Rational("18446744073709551616"));
  EXPECT_FALSE(Rational(0) < Rational(-500));
  EXPECT_FALSE(Rational(1) < Rational(-500));
  EXPECT_FALSE(Rational(-499) < Rational(-500));
  EXPECT_FALSE(Rational(-500) < Rational(-500));
}

TEST(Numbers_Rational, Comparison_EqualToRational) {
  EXPECT_TRUE(Rational(-1) == Rational(-1));
  EXPECT_TRUE(Rational(0) == Rational(0));
  EXPECT_TRUE(Rational(1) == Rational(1));

  EXPECT_FALSE(Rational(-1) == Rational(0));
  EXPECT_FALSE(Rational(-1) == Rational(1));
  EXPECT_FALSE(Rational(0) == Rational(-1));
  EXPECT_FALSE(Rational(0) == Rational(1));
  EXPECT_FALSE(Rational(1) == Rational(-1));
  EXPECT_FALSE(Rational(1) == Rational(0));

  EXPECT_TRUE(Rational(1, -2) == Rational(-1, 2));
}

TEST(Numbers_Rational, Comparison_EqualToInt) {
  EXPECT_TRUE(Rational{-1} == -1);
  EXPECT_TRUE(Rational{0} == 0);
  EXPECT_TRUE(Rational{1} == 1);

  EXPECT_FALSE(Rational{-1} == 0);
  EXPECT_FALSE(Rational{-1} == 1);
  EXPECT_FALSE(Rational{0} == -1);
  EXPECT_FALSE(Rational{0} == 1);
  EXPECT_FALSE(Rational{1} == -1);
  EXPECT_FALSE(Rational{1} == 0);
}
