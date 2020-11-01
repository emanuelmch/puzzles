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

TEST(Numbers, GreatestCommonDivisor) {
  EXPECT_EQ(greatestCommonDivisor(1, 3), 1);
  EXPECT_EQ(greatestCommonDivisor(17, 19), 1);
  EXPECT_EQ(greatestCommonDivisor(10, 25), 5);
  EXPECT_EQ(greatestCommonDivisor(3154, 4522), 38);
}

TEST(Numbers, LowestCommonMultiple) {
  EXPECT_EQ(lowestCommonMultiple(1, 30), 30);
  EXPECT_EQ(lowestCommonMultiple(10, 25), 50);
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
  EXPECT_EQ(std::to_string(Number(-1)), "-1");
  EXPECT_EQ(std::to_string(Number(0)), "0");
  EXPECT_EQ(std::to_string(Number(1)), "1");
}

TEST(Numbers_Number, Addition) {
  Number negativeFive(-5);
  Number negativeOne(-1);
  Number zero(0);
  Number one(1);
  Number two(2);
  Number three(3);
  Number four(4);
  Number five(5);
  Number nine(9);
  Number fifteen(15);
  Number oneHundredTwentyThree(123);
  Number twoHundredThirtyFour(234);
  Number absurdNumberOne("1354645611354413541715318441313195");
  Number absurdNumberTwo("137415147537554114372745478463741");

  Number half(1, 2);
  Number oneOverFiveHundredTwelve(1, 512);
  Number negativeOneOverFiveHundredTwelve(-1, 512);

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

TEST(Numbers_Number, Subtraction) {
  Number zero(0);
  Number one(1);
  Number two(2);
  Number five(5);
  Number ten(10);
  Number hundred(100);

  Number absurdNumberOne(1537, 512);
  Number absurdNumberTwo(1, 8192);

  Number oneOverTwo(1, 2);
  Number threeOverTwo(3, 2);

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

TEST(Numbers_Number, Multiplication) {
  Number negativeFour(-4);
  Number negativeOne(-1);
  Number zero(0);
  Number one(1);
  Number two(2);
  Number four(4);
  Number bigNumber("18446744073709551616");
  Number absurdNumberOne(15630, 6), absurdNumberTwo(5361, 15);

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

TEST(Numbers_Number, Division) {
  Number one(1);
  Number two(2);
  Number five(5);
  Number ten(10);
  Number sixteen(16);
  Number fifty(50);
  Number thousandTwentyFour(1024);
  Number bigNumber(8192);

  EXPECT_EQ(std::to_string(two / one), "2");
  EXPECT_EQ(std::to_string(two / two), "1");
  EXPECT_EQ(std::to_string(ten / two), "5");
  EXPECT_EQ(std::to_string(fifty / two), "25");
  EXPECT_EQ(std::to_string(fifty / ten), "5");
  EXPECT_EQ(std::to_string(thousandTwentyFour / sixteen), "64");
  EXPECT_EQ(std::to_string(bigNumber / sixteen), "512");

  EXPECT_EQ(std::to_string(five / two), "5/2");
  EXPECT_EQ(std::to_string(one / bigNumber), "1/8192");
}

TEST(Numbers_Number, Power) {
  Number negativeFour(-4);
  Number negativeOne(-1);
  Number zero(0);
  Number one(1);
  Number two(2);
  Number three(3);
  Number eight(8);

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

TEST(Numbers_Number, Increment) {
  Number value(0);
  EXPECT_EQ(std::to_string(++value), "1");
  EXPECT_EQ(std::to_string(++value), "2");
  EXPECT_EQ(std::to_string(++value), "3");
  EXPECT_EQ(std::to_string(++value), "4");
  EXPECT_EQ(std::to_string(++value), "5");
  EXPECT_EQ(std::to_string(++value), "6");
  EXPECT_EQ(std::to_string(++value), "7");
  EXPECT_EQ(std::to_string(++value), "8");
  EXPECT_EQ(std::to_string(++value), "9");
  EXPECT_EQ(std::to_string(++value), "10");
  EXPECT_EQ(std::to_string(++value), "11");
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

TEST(Numbers_Number, Comparison_EqualToNumber) {
  EXPECT_TRUE(Number(-1) == Number(-1));
  EXPECT_TRUE(Number(0) == Number(0));
  EXPECT_TRUE(Number(1) == Number(1));

  EXPECT_FALSE(Number(-1) == Number(0));
  EXPECT_FALSE(Number(-1) == Number(1));
  EXPECT_FALSE(Number(0) == Number(-1));
  EXPECT_FALSE(Number(0) == Number(1));
  EXPECT_FALSE(Number(1) == Number(-1));
  EXPECT_FALSE(Number(1) == Number(0));
}

TEST(Numbers_Number, Comparison_EqualToInt) {
  EXPECT_TRUE(Number(-1) == -1);
  EXPECT_TRUE(Number(0) == 0);
  EXPECT_TRUE(Number(1) == 1);

  EXPECT_FALSE(Number(-1) == 0);
  EXPECT_FALSE(Number(-1) == 1);
  EXPECT_FALSE(Number(0) == -1);
  EXPECT_FALSE(Number(0) == 1);
  EXPECT_FALSE(Number(1) == -1);
  EXPECT_FALSE(Number(1) == 0);
}
