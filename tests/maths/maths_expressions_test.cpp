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

#include "maths/expressions.h"

#include <gtest/gtest.h>

using namespace Maths;
using Puzzles::Numbers::Rational;

TEST(Expressions, Evaluator) {
  EXPECT_EQ(evaluateExpression("1 +2"), 3);
  EXPECT_EQ(evaluateExpression("1 + 1"), 2);
  EXPECT_EQ(evaluateExpression("2 + 3"), 5);
  EXPECT_EQ(evaluateExpression("2+3 "), 5);
  EXPECT_EQ(evaluateExpression("2+ 3 +4"), 9);
  EXPECT_EQ(evaluateExpression("2 + 3 - 4"), 1);
  EXPECT_EQ(evaluateExpression("2 - 3 + 4"), 3);
  EXPECT_EQ(evaluateExpression("1 * 2 + 3"), 5);
  EXPECT_EQ(evaluateExpression("1 + 2 * 3"), 7);
  EXPECT_EQ(evaluateExpression("1+2*3/2+4/2-1*3"), 3);
  EXPECT_EQ(evaluateExpression("(1)"), 1);
  EXPECT_EQ(evaluateExpression("(1+1)"), 2);
  EXPECT_EQ(evaluateExpression("1*(2+1)"), 3);
  EXPECT_EQ(evaluateExpression("1+(3+1)/2"), 3);
  EXPECT_EQ(evaluateExpression("2*(3*(1+2)+2)"), 22);
  EXPECT_EQ(evaluateExpression("123*456"), 56088);
  EXPECT_EQ(evaluateExpression("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3 - 1 / 8192"), 3);
  EXPECT_EQ(evaluateExpression("3 + 4 * (2 ^ 2) ^ 3 / ( 1 - 5 ) ^ 2"), 19);
  EXPECT_EQ(evaluateExpression("3 + 4 * 2 ^ 2 ^ 3 / ( 1 - 5 ) ^ 2"), 67);
  EXPECT_EQ(evaluateExpression(" 3 + (4 * 2) ^ 2 ^ 3 ^ 1 ^ 1 / ( 1 - 5 ) ^ 2 ^ 3"), 259);
  EXPECT_EQ(evaluateExpression("-12 + 13"), 1);
  EXPECT_EQ(evaluateExpression("-(5 + 7) + 13"), 1);

  EXPECT_EQ(std::to_string(evaluateExpression("3 + ((4 * 2) ^ 2 ^ 3/ ( 1 - 5 ) ^ 2 ^ 3 ) * 15/154")), "2151/77");
  EXPECT_EQ(std::to_string(evaluateExpression("11 * -10")), "-110");
  EXPECT_EQ(std::to_string(evaluateExpression("9 - 80 - 11 * -10 - -100 / 60 - 28")), "38/3");
  EXPECT_EQ(std::to_string(evaluateExpression("-(1) - (2)")), "-3");
  EXPECT_EQ(std::to_string(evaluateExpression("-(-2)")), "2");
  EXPECT_EQ(std::to_string(evaluateExpression("-(-32) * (79 / -69 - -(13)) - (60 + (((-(50 * 52)))) / 16)")),
            "66497/138");
  EXPECT_EQ(std::to_string(evaluateExpression("(-71) + (2 * 100 / -(60)) + (-46 + -(((-(-29 + -35)))) + 15)")),
            "-508/3");
}

TEST(Expressions, Tokenizer) {
  Token plus('+');
  Token minus('-');
  Token times('*');
  Token divided('/');

  Token open('(');
  Token close(')');

  Token zero(Rational(0));
  Token one(Rational(1));
  Token two(Rational(2));
  Token twelve(Rational(12));
  Token thirteen(Rational(13));
  Token hundredTwentyThree(Rational(123));
  Token thousand(Rational(1000));

  EXPECT_EQ(std::to_string(tokenizeExpression("1+2")), std::to_string(std::vector{one, plus, two}));
  EXPECT_EQ(std::to_string(tokenizeExpression("1000/123")),
            std::to_string(std::vector{thousand, divided, hundredTwentyThree}));
  EXPECT_EQ(std::to_string(tokenizeExpression("0")), std::to_string(std::vector{zero}));

  EXPECT_EQ(std::to_string(tokenizeExpression("-12+13")), std::to_string(std::vector{minus, twelve, plus, thirteen}));
  EXPECT_EQ(std::to_string(tokenizeExpression("-(-1)")), std::to_string(std::vector{minus, open, minus, one, close}));
  EXPECT_EQ(std::to_string(tokenizeExpression("-(1)-1*(2)")),
            std::to_string(std::vector{minus, open, one, close, minus, one, times, open, two, close}));
}
