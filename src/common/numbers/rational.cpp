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

#include "rational.h"

#include "common/assertions.h"
#include "common/numbers/integers.h" // greatestCommonDivisor

using pzl::Integer;
using pzl::Rational;

Rational::Rational(intmax_t numerator, intmax_t denominator)
    : numerator{numerator}, denominator{std::abs(denominator)} {
  ensure(denominator != 0);
  if (denominator < 0) {
    this->numerator *= -1;
  }
}

Rational::Rational(Integer numerator, const Integer &denominator)
    : numerator{std::move(numerator)}, denominator{std::abs(denominator)} {
  ensure(denominator != 0);
  if (denominator < 0) {
    this->numerator *= -1;
  }
}

Rational Rational::operator+(const Rational &o) const {
  auto [left, right, denominator] = normalizeDenominatorWith(o);
  return Rational(left + right, denominator).simplify();
}

Rational Rational::operator-(const Rational &o) const {
  auto [left, right, denominator] = normalizeDenominatorWith(o);
  return Rational(left - right, denominator).simplify();
}

Rational Rational::operator*(const Rational &o) const {
  auto num = this->numerator * o.numerator;
  auto den = this->denominator * o.denominator;

  return Rational(num, den).simplify();
}

Rational Rational::operator/(const Rational &o) const {
  ensure(o != 0); // division by zero is undefined
  if (numerator == 0) {
    return Rational(0);
  }

  ensure(this->denominator == 1 && o.denominator == 1); // Haven't implemented this yet

  // Now for the actual implementation
  Integer remainder = this->numerator.absolute();
  Integer integer(0);
  const auto step = o.numerator.absolute();

  while (remainder >= step) {
    remainder -= step;
    ++integer;
  }

  if (remainder == 0) {
    if (positive() != o.positive()) {
      integer *= -1;
    }
    return Rational(integer);
  } else {
    auto finalNumerator = (integer * step) + remainder;
    if (positive() != o.positive()) {
      finalNumerator *= -1;
    }
    return Rational{finalNumerator, step};
  }
}

Rational Rational::power(const Rational &exp) const {
  ensure(*this != 0 || exp != 0); // zero ^ zero is undefined
  ensure(exp.positive());         // Haven't implemented this yet
  ensure(exp.denominator == 1);   // Haven't implemented this yet

  // Integer power is faster than Rational power
  if (this->denominator == 1) {
    auto result = std::pow(this->numerator, exp.numerator);
    return Rational(result, Integer(1));
  }

  Rational result(1);

  for (Integer i{0}; i < exp.numerator; ++i) {
    result *= *this;
  }

  return result;
}

bool Rational::operator<(const Rational &o) const {
  ensure(this->denominator > 0);
  ensure(o.denominator > 0);

  if (this->positive() != o.positive()) {
    return o.positive();
  }

  auto [us, them, _] = normalizeDenominatorWith(o);
  UNUSED(_);

  return us < them;
}

bool Rational::operator==(const Rational &o) const {
  ensure(this->denominator > 0);
  ensure(o.denominator > 0);

  return this->denominator == o.denominator && this->numerator == o.numerator;
}

std::string Rational::toString() const {
  ensure(denominator > 0);
  auto result = std::to_string(numerator);

  if (denominator != 1) {
    result += "/" + std::to_string(denominator);
  }

  return result;
}

std::tuple<Integer, Integer, Integer> Rational::normalizeDenominatorWith(const Rational &o) const {
  if (denominator == o.denominator) return std::make_tuple(this->numerator, o.numerator, this->denominator);

  auto leftNumerator = this->numerator;
  auto leftDenominator = this->denominator;
  auto rightNumerator = o.numerator;
  auto rightDenominator = o.denominator;

  auto newDenominator = lowestCommonMultiple(leftDenominator, rightDenominator);

  auto left = (newDenominator / leftDenominator) * leftNumerator;
  auto right = (newDenominator / rightDenominator) * rightNumerator;

  return std::make_tuple(left, right, newDenominator);
}

Rational &Rational::simplify() {
  if (numerator == 0) {
    denominator = Integer{1};
  }
  if (denominator == 1) return *this;

  auto gcd = greatestCommonDivisor(numerator, denominator);
  this->numerator /= gcd;
  this->denominator /= gcd;

  return *this;
}
