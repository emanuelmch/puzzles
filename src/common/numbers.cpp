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

#include <cassert>
#include <cinttypes>

using namespace Puzzles::Numbers;

Number::Number(std::string value) : numerator(std::move(value)), denominator("1"), positive(true) {
  // TODO: assert there are no invalid characters
  if (numerator[0] == '-') {
    numerator = numerator.substr(1);
    positive = false;
  }
  assert(!denominator.empty());
}

Number::Number(intmax_t value) : Number(std::to_string(value)) {}

Number::Number(intmax_t _n, uintmax_t _d) : Number(_n >= 0 ? _n : _n * -1, _d, _n >= 0) {}

Number::Number(uintmax_t numerator, uintmax_t denominator, bool positive)
    : numerator(std::to_string(numerator)), denominator(std::to_string(denominator)), positive(positive) {}

template <typename iterator, typename iterator_end, typename T>
inline T nextAndAdvance(iterator *it, const iterator_end &end, T defaultValue) {
  if (*it == end) {
    return defaultValue;
  } else {
    T value = **it;
    std::advance(*it, 1);
    return value;
  }
}

Number Number::operator+(const Number &o) const {
  assert(positive && o.positive); // Haven't implemented this yet
  auto [left, right] = normalizeDenominatorWith(o);

  auto lit = left.numerator.crbegin();
  auto rit = right.numerator.crbegin();
  std::string finalSum;
  auto carryOver = 0;

  while (lit != left.numerator.crend() || rit != right.numerator.crend()) {
    auto leftDigit = ctoi(nextAndAdvance(&lit, left.numerator.crend(), '0'));
    auto rightDigit = ctoi(nextAndAdvance(&rit, right.numerator.crend(), '0'));
    auto digitSum = leftDigit + rightDigit + carryOver;

    if (digitSum > 9) {
      carryOver = 1;
      digitSum -= 10;
    } else {
      carryOver = 0;
    }

    finalSum = itoc(digitSum) + finalSum;
  }
  if (carryOver) {
    finalSum = "1" + finalSum;
  }

  Number result(finalSum);
  result.denominator = left.denominator;
  result.positive = left.positive;
  result.simplify();

  return result;
}

bool Number::operator<(const Number &o) const {
  if (this->positive != o.positive) {
    return o.positive;
  }

  auto [us, them] = normalizeDenominatorWith(o);
  if (us == them) return false;

  if (us.numerator.length() != them.numerator.length()) {
    return (us.numerator.length() < them.numerator.length()) == us.positive;
  }

  for (auto lit = us.numerator.cbegin(), rit = them.numerator.cbegin(); lit < us.numerator.cend(); ++lit, ++rit) {
    auto leftDigit = *lit;
    auto rightDigit = *rit;
    if (leftDigit == rightDigit) continue;

    return (leftDigit < rightDigit) == us.positive;
  }

  assert(!"Should never get here");
  return false;
}

bool Number::operator==(const Number &o) const {
  return this->positive == o.positive && this->denominator == o.denominator && this->numerator == o.numerator;
}

std::string Number::toString() const {
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
  assert(Number(denominator) < Number(std::numeric_limits<uint32_t>::max()));
  assert(Number(o.denominator) < Number(std::numeric_limits<uint32_t>::max()));

  uint32_t leftDenominator = strtoumax(this->denominator.c_str(), nullptr, 10);
  uint32_t leftNumerator = strtoumax(this->numerator.c_str(), nullptr, 10);
  uint32_t rightDenominator = strtoumax(o.denominator.c_str(), nullptr, 10);
  uint32_t rightNumerator = strtoumax(o.numerator.c_str(), nullptr, 10);
  // TODO: This could be more efficient, we don't actually have to go that high every time
  uint64_t newDenominator = leftDenominator * rightDenominator;

  auto left = newDenominator / leftDenominator * leftNumerator;
  auto right = newDenominator / rightDenominator * rightNumerator;

  return std::pair(Number(left, newDenominator, this->positive), Number(right, newDenominator, o.positive));
}

void Number::simplify() {
  if (denominator == "1") return;

  // FIXME: Actually implement this function after we have other operators done
  if (numerator == denominator) {
    numerator = "1";
    denominator = "1";
  }
}
