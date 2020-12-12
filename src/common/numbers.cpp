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
#include "compat/defs.h"

#include <algorithm>
#include <cinttypes>
#include <utility>

using namespace Puzzles::Numbers;

inline std::string_view fitNumerator(const std::string_view &original) {
  if (original.empty()) return original;

  auto value = (original[0] == '-') ? original.substr(1) : original;
  return Puzzles::trimLeadingView(value, '0');
}

Rational::Rational(const std::string &value)
    : numerator(fitNumerator(value)), denominator("1"), positive(value.empty() || value[0] != '-') {
  ensure(numerator.find_first_not_of("0123456789") == numerator.npos);
}

Rational::Rational(intmax_t value) : Rational(std::to_string(value)) {}

Rational::Rational(intmax_t _n, uintmax_t _d) : Rational(static_cast<uintmax_t>(std::abs(_n)), _d, _n >= 0) {}

Rational::Rational(uintmax_t numerator, uintmax_t denominator, bool positive)
    : Rational(std::to_string(numerator), std::to_string(denominator), positive) {}

Rational::Rational(const std::string &_numerator, std::string _denominator, bool positive)
    : numerator(trimLeadingView(_numerator, '0')), denominator(std::move(_denominator)), positive(positive) {
  ensure(numerator.find_first_not_of("0123456789") == numerator.npos);
  ensure(denominator.find_first_not_of("0123456789") == denominator.npos);
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

#ifdef __cpp_lib_three_way_comparison
    auto digitComparison = leftDigit <=> rightDigit;
    if (digitComparison == std::strong_ordering::equal) [[pzl_likely]] {
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

Rational Rational::operator+(const Rational &o) const {
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

  Rational result(finalSum, left.denominator, finalSign);
  result.simplify();

  return result;
}

Rational Rational::operator-(const Rational &o) const {
  Rational negatedOther(o.numerator, o.denominator, !o.positive);
  return *this + negatedOther;
}

inline Rational multiply(const std::string &_min, const std::string &_max) {
  const Rational min(_min);
  const Rational max(_max);

  Rational result(0);
  for (Rational i(0); i < min; ++i) {
    result += max;
  }

  return result;
}

Rational Rational::operator*(const Rational &o) const {
  auto finalSign = this->positive == o.positive;

  auto [us, them] = normalizeDenominatorWith(o);
  auto absCmp = compareIntegers(us.numerator, them.numerator);
  auto [min, max] = (absCmp == compat::strong_ordering::less) ? std::pair(us, them) : std::pair(them, us);

  if (min == 1) {
    return Rational(max.numerator, max.denominator, finalSign);
  }

  auto num = multiply(min.numerator, max.numerator).numerator;
  auto den = multiply(min.denominator, max.denominator).numerator;

  Rational result(num, den, finalSign);
  result.simplify();
  return result;
}

Rational Rational::operator/(const Rational &o) const {
  ensure(o != 0); // division by zero is undefined
  if (numerator == "0") {
    return Rational(0);
  }

  auto sameSign = this->positive == o.positive;
  if (o.numerator == "1" && o.denominator == "1") {
    return Rational(numerator, denominator, sameSign);
  }

  ensure(this->denominator == "1" && o.denominator == "1"); // Haven't implemented this yet

  auto result = division(this->numerator, o.numerator);
  return Rational(result.numerator, result.denominator, sameSign);
}

Rational Rational::division(const std::string &_numerator, const std::string &_denominator) {
  Rational remainder(_numerator);
  Rational factor(_denominator);
  Rational integer(0);

  while (remainder >= factor) {
    remainder -= factor;
    ++integer;
  }

  if (remainder == 0) {
    return integer;
  } else {
    Rational rational(remainder.numerator, _denominator, true);
    return integer + rational;
  }
}

Rational Rational::power(const Rational &exp) const {
  ensure(*this != 0 || exp != 0); // zero ^ zero is undefined
  ensure(exp.positive);           // Haven't implemented this yet;
  Rational result(1);

  for (Rational i(0); i < exp; ++i) {
    result *= *this;
  }

  return result;
}

Rational &Rational::operator++() {
  copy(*this + Rational(1));
  return *this;
}

bool Rational::operator<(const Rational &o) const {
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

bool Rational::operator==(const Rational &o) const {
  return this->positive == o.positive && this->denominator == o.denominator && this->numerator == o.numerator;
}

bool Rational::operator==(intmax_t o) const {
  if (o == 0) return numerator.empty();

  return this->denominator == "1" && this->positive == (o >= 0) && this->numerator == std::to_string(std::abs(o));
}

std::string Rational::toString() const {
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

std::pair<Rational, Rational> Rational::normalizeDenominatorWith(const Rational &o) const {
  if (denominator == o.denominator) return std::pair(*this, o);

  // FIXME: Use rationals here after we've implemented operator* and remove these two ensures
  ensure(Rational(denominator) < Rational(std::numeric_limits<uint32_t>::max()));
  ensure(Rational(o.denominator) < Rational(std::numeric_limits<uint32_t>::max()));

  uint32_t leftDenominator = strtoumax(this->denominator.c_str(), nullptr, 10);
  uint32_t leftNumerator = strtoumax(this->numerator.c_str(), nullptr, 10);
  uint32_t rightDenominator = strtoumax(o.denominator.c_str(), nullptr, 10);
  uint32_t rightNumerator = strtoumax(o.numerator.c_str(), nullptr, 10);
  uint64_t newDenominator = lowestCommonMultiple(leftDenominator, rightDenominator);

  auto left = newDenominator / leftDenominator * leftNumerator;
  auto right = newDenominator / rightDenominator * rightNumerator;

  return std::pair(Rational(left, newDenominator, this->positive), Rational(right, newDenominator, o.positive));
}

void Rational::simplify() {
  if (numerator.empty()) denominator = "1";
  if (denominator == "1") return;

  // Haven't implemented these two yet
  ensure_m(Rational(numerator) <= Rational(std::to_string(std::numeric_limits<uintmax_t>::max())),
           numerator << " > " << std::numeric_limits<uintmax_t>::max());
  ensure_m(Rational(denominator) <= Rational(std::to_string(std::numeric_limits<uintmax_t>::max())),
           denominator << " > " << std::numeric_limits<uintmax_t>::max());
  auto num = std::strtoumax(numerator.c_str(), nullptr, 10);
  auto den = std::strtoumax(denominator.c_str(), nullptr, 10);

  // oh boy
  auto gcd = greatestCommonDivisor(num, den);
  while (gcd > 1) {
    num /= gcd;
    den /= gcd;

    gcd = greatestCommonDivisor(num, den);
  }

  this->numerator = std::to_string(num);
  this->denominator = std::to_string(den);
}
