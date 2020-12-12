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

TEST(Integer, Addition) {
  Integer negativeFive{-5};
  Integer negativeOne{-1};
  Integer zero{0};
  Integer one{1};
  Integer two{2};
  Integer three{3};
  Integer four{4};
  Integer five{5};
  Integer nine{9};
  Integer fifteen{15};
  Integer oneHundredTwentyThree{123};
  Integer twoHundredThirtyFour{234};
  Integer absurdIntegerOne{"1354645611354413541715318441313195"};
  Integer absurdIntegerTwo{"137415147537554114372745478463741"};

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
  EXPECT_EQ(std::to_string(absurdIntegerOne + zero), "1354645611354413541715318441313195");
  EXPECT_EQ(std::to_string(absurdIntegerOne + absurdIntegerTwo), "1492060758891967656088063919776936");

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

TEST(Integer, Addition_Int) {
  Integer negativeFive{-5};
  Integer negativeOne{-1};
  Integer zero{0};
  Integer one{1};
  Integer five{5};
  Integer bigNumber{1234567890};

  EXPECT_EQ(std::to_string(negativeFive + (-5)), "-10");
  EXPECT_EQ(std::to_string(negativeFive + (-1)), "-6");
  EXPECT_EQ(std::to_string(negativeFive + 0), "-5");
  EXPECT_EQ(std::to_string(negativeFive + 1), "-4");
  EXPECT_EQ(std::to_string(negativeFive + 5), "0");
  EXPECT_EQ(std::to_string(negativeFive + 1234567890), "1234567885");

  EXPECT_EQ(std::to_string(negativeOne + (-5)), "-6");
  EXPECT_EQ(std::to_string(negativeOne + (-1)), "-2");
  EXPECT_EQ(std::to_string(negativeOne + 0), "-1");
  EXPECT_EQ(std::to_string(negativeOne + 1), "0");
  EXPECT_EQ(std::to_string(negativeOne + 5), "4");
  EXPECT_EQ(std::to_string(negativeOne + 1234567890), "1234567889");

  EXPECT_EQ(std::to_string(zero + (-5)), "-5");
  EXPECT_EQ(std::to_string(zero + (-1)), "-1");
  EXPECT_EQ(std::to_string(zero + 0), "0");
  EXPECT_EQ(std::to_string(zero + 1), "1");
  EXPECT_EQ(std::to_string(zero + 5), "5");
  EXPECT_EQ(std::to_string(zero + 1234567890), "1234567890");

  EXPECT_EQ(std::to_string(one + (-5)), "-4");
  EXPECT_EQ(std::to_string(one + (-1)), "0");
  EXPECT_EQ(std::to_string(one + 0), "1");
  EXPECT_EQ(std::to_string(one + 1), "2");
  EXPECT_EQ(std::to_string(one + 5), "6");
  EXPECT_EQ(std::to_string(one + 1234567890), "1234567891");

  EXPECT_EQ(std::to_string(five + (-5)), "0");
  EXPECT_EQ(std::to_string(five + (-1)), "4");
  EXPECT_EQ(std::to_string(five + 0), "5");
  EXPECT_EQ(std::to_string(five + 1), "6");
  EXPECT_EQ(std::to_string(five + 5), "10");
  EXPECT_EQ(std::to_string(five + 1234567890), "1234567895");

  EXPECT_EQ(std::to_string(bigNumber + (-5)), "1234567885");
  EXPECT_EQ(std::to_string(bigNumber + (-1)), "1234567889");
  EXPECT_EQ(std::to_string(bigNumber + 0), "1234567890");
  EXPECT_EQ(std::to_string(bigNumber + 1), "1234567891");
  EXPECT_EQ(std::to_string(bigNumber + 5), "1234567895");
  EXPECT_EQ(std::to_string(bigNumber + 1234567890), "2469135780");
}

TEST(Integer, Subtraction) {
  Integer zero{0};
  Integer one{1};
  Integer two{2};
  Integer five{5};
  Integer ten{10};
  Integer hundred{100};

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
}

TEST(Integer, Multiplication) {
  Integer negativeFour{-4};
  Integer negativeOne{-1};
  Integer zero{0};
  Integer one{1};
  Integer two{2};
  Integer four{4};
  Integer bigInteger{"18446744073709551616"};

  EXPECT_EQ(std::to_string(zero * zero), "0");
  EXPECT_EQ(std::to_string(zero * one), "0");
  EXPECT_EQ(std::to_string(one * zero), "0");
  EXPECT_EQ(std::to_string(one * one), "1");
  EXPECT_EQ(std::to_string(one * two), "2");
  EXPECT_EQ(std::to_string(two * one), "2");
  EXPECT_EQ(std::to_string(two * four), "8");
  EXPECT_EQ(std::to_string(four * two), "8");
  EXPECT_EQ(std::to_string(bigInteger * zero), "0");
  EXPECT_EQ(std::to_string(zero * bigInteger), "0");
  EXPECT_EQ(std::to_string(bigInteger * one), "18446744073709551616");
  EXPECT_EQ(std::to_string(one * bigInteger), "18446744073709551616");
  EXPECT_EQ(std::to_string(two * bigInteger), "36893488147419103232");

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
}

TEST(Integer, Division) {
  Integer one{1};
  Integer two{2};
  Integer five{5};
  Integer ten{10};
  Integer sixteen{16};
  Integer fifty{50};
  Integer thousandTwentyFour{1024};
  Integer bigInteger{8192};

  EXPECT_EQ(std::to_string(two / one), "2");
  EXPECT_EQ(std::to_string(two / two), "1");
  EXPECT_EQ(std::to_string(ten / two), "5");
  EXPECT_EQ(std::to_string(fifty / two), "25");
  EXPECT_EQ(std::to_string(fifty / ten), "5");
  EXPECT_EQ(std::to_string(thousandTwentyFour / sixteen), "64");
  EXPECT_EQ(std::to_string(bigInteger / sixteen), "512");
}

TEST(Integer, Modulo) {
  Integer five{5};
  Integer fifty{50};
  Integer fiftyTwo{52};

  EXPECT_EQ(std::to_string(five % five), "0");
  EXPECT_EQ(std::to_string(fifty % five), "0");
  EXPECT_EQ(std::to_string(fiftyTwo % five), "2");

  EXPECT_EQ(std::to_string(five % fifty), "5");
  EXPECT_EQ(std::to_string(fifty % fifty), "0");
  EXPECT_EQ(std::to_string(fiftyTwo % fifty), "2");

  EXPECT_EQ(std::to_string(five % fiftyTwo), "5");
  EXPECT_EQ(std::to_string(fifty % fiftyTwo), "50");
  EXPECT_EQ(std::to_string(fiftyTwo % fiftyTwo), "0");
}

TEST(Integer, Power) {
  Integer negativeFour{-4};
  Integer negativeOne{-1};
  Integer zero{0};
  Integer one{1};
  Integer two{2};
  Integer three{3};
  Integer eight{8};

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

TEST(Integer, Comparison_EqualTo) {
  EXPECT_TRUE(Integer{-1} == Integer{-1});
  EXPECT_TRUE(Integer{0} == Integer{0});
  EXPECT_TRUE(Integer{1} == Integer{1});

  EXPECT_FALSE(Integer{-1} == Integer{0});
  EXPECT_FALSE(Integer{-1} == Integer{1});
  EXPECT_FALSE(Integer{0} == Integer{-1});
  EXPECT_FALSE(Integer{0} == Integer{1});
  EXPECT_FALSE(Integer{1} == Integer{-1});
  EXPECT_FALSE(Integer{1} == Integer{0});
}

TEST(Integer, Comparison_EqualToInt) {
  EXPECT_TRUE(Integer{-1} == -1);
  EXPECT_TRUE(Integer{0} == 0);
  EXPECT_TRUE(Integer{1} == 1);

  EXPECT_FALSE(Integer{-1} == 0);
  EXPECT_FALSE(Integer{-1} == 1);
  EXPECT_FALSE(Integer{0} == -1);
  EXPECT_FALSE(Integer{0} == 1);
  EXPECT_FALSE(Integer{1} == -1);
  EXPECT_FALSE(Integer{1} == 0);
}

TEST(Integer, Comparison_NotEqualTo) {
  EXPECT_TRUE(Integer{-1} != Integer{0});
  EXPECT_TRUE(Integer{-1} != Integer{1});
  EXPECT_TRUE(Integer{0} != Integer{-1});
  EXPECT_TRUE(Integer{0} != Integer{1});
  EXPECT_TRUE(Integer{1} != Integer{-1});
  EXPECT_TRUE(Integer{1} != Integer{0});

  EXPECT_FALSE(Integer{-1} != Integer{-1});
  EXPECT_FALSE(Integer{0} != Integer{0});
  EXPECT_FALSE(Integer{1} != Integer{1});
}

TEST(Integer, Comparison_NotEqualToInt) {
  EXPECT_TRUE(Integer{-1} != 0);
  EXPECT_TRUE(Integer{-1} != 1);
  EXPECT_TRUE(Integer{0} != -1);
  EXPECT_TRUE(Integer{0} != 1);
  EXPECT_TRUE(Integer{1} != -1);
  EXPECT_TRUE(Integer{1} != 0);

  EXPECT_FALSE(Integer{-1} != -1);
  EXPECT_FALSE(Integer{0} != 0);
  EXPECT_FALSE(Integer{1} != 1);
}

TEST(Integer, Comparison_LessThan) {
  EXPECT_TRUE(Integer{0} < Integer{1});
  EXPECT_TRUE(Integer{9} < Integer{10});
  EXPECT_TRUE(Integer{"18446744073709551615"} < Integer{"18446744073709551616"});
  EXPECT_TRUE(Integer{-500} < Integer{0});
  EXPECT_TRUE(Integer{-500} < Integer{1});
  EXPECT_TRUE(Integer{-500} < Integer{-499});

  EXPECT_FALSE(Integer{0} < Integer{0});
  EXPECT_FALSE(Integer{1} < Integer{0});
  EXPECT_FALSE(Integer{10} < Integer{9});
  EXPECT_FALSE(Integer{"18446744073709551616"} < Integer{"18446744073709551616"});
  EXPECT_FALSE(Integer{0} < Integer{-500});
  EXPECT_FALSE(Integer{1} < Integer{-500});
  EXPECT_FALSE(Integer{-499} < Integer{-500});
  EXPECT_FALSE(Integer{-500} < Integer{-500});
}

TEST(Integer, Comparison_LessThanOrEqualTo) {
  EXPECT_TRUE(Integer{0} <= Integer{1});
  EXPECT_TRUE(Integer{0} <= Integer{0});
  EXPECT_TRUE(Integer{9} <= Integer{10});
  EXPECT_TRUE(Integer{"18446744073709551615"} <= Integer{"18446744073709551616"});
  EXPECT_TRUE(Integer{"18446744073709551616"} <= Integer{"18446744073709551616"});
  EXPECT_TRUE(Integer{-500} <= Integer{0});
  EXPECT_TRUE(Integer{-500} <= Integer{1});
  EXPECT_TRUE(Integer{-500} <= Integer{-499});
  EXPECT_TRUE(Integer{-500} <= Integer{-500});

  EXPECT_FALSE(Integer{1} <= Integer{0});
  EXPECT_FALSE(Integer{10} <= Integer{9});
  EXPECT_FALSE(Integer{"18446744073709551616"} <= Integer{"18446744073709551615"});
  EXPECT_FALSE(Integer{0} <= Integer{-500});
  EXPECT_FALSE(Integer{1} <= Integer{-500});
  EXPECT_FALSE(Integer{-499} <= Integer{-500});
}

TEST(Integer, Increment) {
  Integer value{-10};
  EXPECT_EQ(std::to_string(++value), "-9");
  EXPECT_EQ(std::to_string(++value), "-8");
  EXPECT_EQ(std::to_string(++value), "-7");
  EXPECT_EQ(std::to_string(++value), "-6");
  EXPECT_EQ(std::to_string(++value), "-5");
  EXPECT_EQ(std::to_string(++value), "-4");
  EXPECT_EQ(std::to_string(++value), "-3");
  EXPECT_EQ(std::to_string(++value), "-2");
  EXPECT_EQ(std::to_string(++value), "-1");
  EXPECT_EQ(std::to_string(++value), "0");
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

  Integer bigPositive{999999998};
  EXPECT_EQ(std::to_string(++bigPositive), "999999999");
  EXPECT_EQ(std::to_string(++bigPositive), "1000000000");
  EXPECT_EQ(std::to_string(++bigPositive), "1000000001");

  Integer bigNegative{-1000000002};
  EXPECT_EQ(std::to_string(++bigNegative), "-1000000001");
  EXPECT_EQ(std::to_string(++bigNegative), "-1000000000");
  EXPECT_EQ(std::to_string(++bigNegative), "-999999999");
}
