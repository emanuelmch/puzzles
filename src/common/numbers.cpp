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

#include "numbers.h"

#include "common/assertions.h"
#include "common/strings.h"
#include "compat/compare.h"

#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <utility>

using namespace Puzzles::Numbers;

Number::Number(std::string value) : numerator(std::move(value)), denominator("1"), positive(true) {
  // TODO: assert there are no invalid characters
  if (!numerator.empty() && numerator[0] == '-') {
    numerator = numerator.substr(1);
    positive = false;
  }
  numerator = trimLeadingView(numerator, '0');
}

Number::Number(intmax_t value) : Number(std::to_string(value)) {}

Number::Number(intmax_t _n, uintmax_t _d) : Number(_n >= 0 ? _n : _n * -1, _d, _n >= 0) {}

Number::Number(uintmax_t numerator, uintmax_t denominator, bool positive)
    : Number(std::to_string(numerator), std::to_string(denominator), positive) {}

Number::Number(std::string _numerator, std::string _denominator, bool positive)
    : numerator(std::move(_numerator)), denominator(std::move(_denominator)), positive(positive) {
  // TODO: assert there are no invalid characters
  numerator = trimLeadingView(numerator, '0');
}

template <typename iterator>
inline char valueAndAdvance(iterator *it) {
  char value = **it;
  std::advance(*it, 1);
  return value;
}

compat::strong_ordering compareIntegers(const std::string &left, const std::string &right) {
  ensure(left.empty() || left[0] != '0');
  ensure(right.empty() || right[0] != '0');

#ifdef __cpp_lib_three_way_comparison
  auto lengthComparison = left.length() <=> right.length();
  if (lengthComparison != std::strong_ordering::equal) {
    return lengthComparison;
  }
#else
  if (left.length() != right.length()) {
    return left.length() < right.length() ? compat::strong_ordering::less : compat::strong_ordering::greater;
  }
#endif

  auto lit = left.cbegin(), rit = right.cbegin();
  while (lit != left.cend()) {
    ensure(rit != right.cend());
    auto leftDigit = *lit;
    auto rightDigit = *rit;

#if defined(__cpp_lib_three_way_comparison) && __has_cpp_attribute(likely)
    auto digitComparison = leftDigit <=> rightDigit;
    if (digitComparison == std::strong_ordering::equal) [[likely]] {
      ++lit;
      ++rit;
      continue;
    }

    return digitComparison;
#else
    if (leftDigit == rightDigit) {
      ++lit;
      ++rit;
      continue;
    }

    return (leftDigit < rightDigit) ? compat::strong_ordering::less : compat::strong_ordering::greater;
#endif
  }

  return compat::strong_ordering::equal;
}

Number Number::operator+(const Number &o) const {
  auto [left, right] = normalizeDenominatorWith(o);
  auto sameSign = left.positive == right.positive;
  auto finalSign = left.positive;

  if (!sameSign && compareIntegers(left.numerator, right.numerator) == compat::strong_ordering::less) {
    std::swap(left.numerator, right.numerator);
    finalSign = right.positive;
  }

  auto lit = left.numerator.crbegin();
  auto rit = right.numerator.crbegin();
  auto carryOver = 0;

  std::string finalSum;
  finalSum.reserve(std::max(left.numerator.length(), right.numerator.length()) + 1);

  while (lit != left.numerator.crend() || rit != right.numerator.crend()) {
    auto leftDigit = lit == left.numerator.crend() ? 0 : ctoi(valueAndAdvance(&lit));
    auto rightDigit = rit == right.numerator.crend() ? 0 : ctoi(valueAndAdvance(&rit));
    auto digitSum = sameSign ? leftDigit + rightDigit + carryOver : leftDigit - rightDigit - carryOver;

    ensure_m(digitSum >= -9 && digitSum <= 19, "digitSum is " << int(digitSum));
    if (digitSum > 9) {
      carryOver = 1;
      digitSum -= 10;
    } else if (digitSum < 0) {
      carryOver = 1;
      digitSum += 10;
    } else {
      carryOver = 0;
    }

    finalSum += itoc(digitSum);
  }

  ensure(carryOver == 0 || (carryOver == 1 && sameSign));
  if (carryOver) {
    finalSum += '1';
  }

  std::reverse(finalSum.begin(), finalSum.end());

  Number result(finalSum, left.denominator, finalSign);
  result.simplify();

  return result;
}

Number Number::operator-(const Number &o) const {
  Number negatedOther(o.numerator, o.denominator, !o.positive);
  return *this + negatedOther;
}

inline Number multiply(const std::string &_min, const std::string &_max) {
  const Number min(_min);
  const Number max(_max);

  Number result(0);
  for (Number i(0); i < min; ++i) {
    result += max;
  }

  return result;
}

Number Number::operator*(const Number &o) const {
  auto finalSign = this->positive == o.positive;

  auto [us, them] = normalizeDenominatorWith(o);
  auto absCmp = compareIntegers(us.numerator, them.numerator);
  auto [min, max] = (absCmp == compat::strong_ordering::less) ? std::pair(us, them) : std::pair(them, us);

  if (min == 1) {
    return Number(max.numerator, max.denominator, finalSign);
  }

  auto num = multiply(min.numerator, max.numerator).numerator;
  auto den = multiply(min.denominator, max.denominator).numerator;

  Number result(num, den, finalSign);
  result.simplify();
  return result;
}

Number Number::operator/(const Number &o) const {
  assert(o != 0); // division by zero is undefined
  if (numerator == "0") {
    return Number(0);
  }

  auto sameSign = this->positive == o.positive;
  if (o.numerator == "1" && o.denominator == "1") {
    return Number(numerator, denominator, sameSign);
  }

  ensure(this->denominator == "1" && o.denominator == "1"); // Haven't implemented this yet

  if (*this < o) {
    Number result(this->numerator, o.numerator, sameSign);
    result.simplify();
    return result;
  }

  // Now for the actual implementation
  Number remainder(this->numerator);
  Number integer(0);

  while (remainder >= o) {
    remainder -= o;
    ++integer;
  }

  if (remainder == 0) {
    integer.positive = sameSign;
    return integer;
  } else {
    Number rational(remainder.numerator, o.numerator, sameSign);
    rational.simplify();
    return integer + rational;
  }
}

Number Number::power(const Number &exp) const {
  assert(*this != 0 || exp != 0); // zero ^ zero is undefined
  ensure(exp.positive);           // Haven't implemented this yet;
  Number result(1);

  for (Number i(0); i < exp; ++i) {
    result *= *this;
  }

  return result;
}

Number &Number::operator++() {
  copy(*this + Number(1));
  return *this;
}

bool Number::operator<(const Number &o) const {
  if (this->positive != o.positive) {
    return o.positive;
  }

  auto [us, them] = normalizeDenominatorWith(o);
  auto result = compareIntegers(us.numerator, them.numerator);
  if (this->positive) {
    return result == compat::strong_ordering::less;
  } else {
    return result == compat::strong_ordering::greater;
  }
}

bool Number::operator==(const Number &o) const {
  return this->positive == o.positive && this->denominator == o.denominator && this->numerator == o.numerator;
}

bool Number::operator==(intmax_t o) const {
  if (o == 0) return numerator.empty();

  return this->denominator == "1" && this->positive == (o >= 0) && this->numerator == std::to_string(std::abs(o));
}

std::string Number::toString() const {
  if (numerator.empty()) return "0";

  auto result = numerator;

  if (denominator != "1") {
    result += "/" + denominator;
  }

  if (!positive) {
    result = "-" + result;
  }

  return result;
}

std::pair<Number, Number> Number::normalizeDenominatorWith(const Number &o) const {
  if (denominator == o.denominator) return std::pair(*this, o);

  // FIXME: Use numbers here after we've implemented operator* and remove these two asserts
  ensure(Number(denominator) < Number(std::numeric_limits<uint32_t>::max()));
  ensure(Number(o.denominator) < Number(std::numeric_limits<uint32_t>::max()));

  uint32_t leftDenominator = strtoumax(this->denominator.c_str(), nullptr, 10);
  uint32_t leftNumerator = strtoumax(this->numerator.c_str(), nullptr, 10);
  uint32_t rightDenominator = strtoumax(o.denominator.c_str(), nullptr, 10);
  uint32_t rightNumerator = strtoumax(o.numerator.c_str(), nullptr, 10);
  uint64_t newDenominator = lowestCommonMultiple(leftDenominator, rightDenominator);

  auto left = newDenominator / leftDenominator * leftNumerator;
  auto right = newDenominator / rightDenominator * rightNumerator;

  return std::pair(Number(left, newDenominator, this->positive), Number(right, newDenominator, o.positive));
}

void Number::simplify() {
  if (numerator == "0") denominator = "1";
  if (denominator == "1") return;

  if (numerator == denominator) {
    numerator = "1";
    denominator = "1";
    return;
  }

  // FIXME: Use numbers here instead of umax
  auto num = std::strtoumax(numerator.c_str(), nullptr, 10);
  auto den = std::strtoumax(denominator.c_str(), nullptr, 10);

  auto div = std::lldiv(num, den);
  if (div.rem == 0) {
    this->numerator = std::to_string(div.quot);
    this->denominator = "1";
    return;
  }
  // oh boy
  auto factor = greatestCommonDivisor(num, den);
  while (factor > 1) {
    num = num / factor;
    den = den / factor;

    factor = greatestCommonDivisor(num, den);
  }

  this->numerator = std::to_string(num);
  this->denominator = std::to_string(den);
}
