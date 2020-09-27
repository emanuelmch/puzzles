/*
 * Copyright (c) 2018 Emanuel Machado da Silva
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

#pragma once

#include "common/assertions.h"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>

namespace Puzzles::Numbers {

constexpr uint8_t ctoi(char c) {
  ensure(c >= '0' && c <= '9');
  return static_cast<uint8_t>(c - '0');
}

constexpr char itoc(uint8_t i) {
  ensure(i < 10);
  return static_cast<char>(i + '0');
}

constexpr uintmax_t factorial(uintmax_t value) {
  return (value < 2) ? 1 : value * factorial(value - 1);
}

template <typename Target, typename Input>
constexpr bool fits(Input value) {
  return value >= std::numeric_limits<Target>::min() && value <= std::numeric_limits<Target>::max();
}

constexpr uintmax_t greatestCommonDivisor(uintmax_t lhs, uintmax_t rhs) {
  // This is the Euclidean algorithm
  if (lhs == 0) return rhs;
  while (true) {
    if (rhs == 0) return lhs;
    lhs %= rhs;
    if (lhs == 0) return rhs;
    rhs %= lhs;
  }
}

constexpr uintmax_t lowestCommonMultiple(uintmax_t lhs, uintmax_t rhs) {
  ensure(lhs != 0 && rhs != 0); // This is undefined
  auto gcd = greatestCommonDivisor(lhs, rhs);
  return lhs * rhs / gcd;
}

struct Number {

  explicit Number(const std::string &);
  explicit Number(intmax_t);
  Number(intmax_t, uintmax_t);

  [[nodiscard]] Number operator+(const Number &) const;
  [[nodiscard]] Number operator-(const Number &) const;
  [[nodiscard]] Number operator*(const Number &) const;
  [[nodiscard]] Number operator/(const Number &) const;

  [[nodiscard]] Number power(const Number &exponent) const;

  void operator+=(const Number &o) { copy(*this + o); }
  void operator-=(const Number &o) { copy(*this - o); }
  void operator*=(const Number &o) { copy(*this * o); }
  Number &operator++();

  [[nodiscard]] bool operator<(const Number &) const;
  // TODO: <= Could be more efficient
  [[nodiscard]] inline bool operator<=(const Number &o) const { return *this < o || *this == o; }
  [[nodiscard]] inline bool operator>=(const Number &o) const { return o < *this; }
  [[nodiscard]] bool operator==(const Number &) const;
  [[nodiscard]] bool operator==(intmax_t) const;
  [[nodiscard]] inline bool operator!=(intmax_t o) const { return !(*this == o); }

  [[nodiscard]] std::string toString() const;

private:
  std::string numerator;
  std::string denominator;
  bool positive;

  Number(uintmax_t, uintmax_t, bool);
  Number(const std::string &, std::string, bool);

  inline void copy(const Number &o) {
    this->numerator = o.numerator;
    this->denominator = o.denominator;
    this->positive = o.positive;
  }

  [[nodiscard]] inline Number absolute() const { return Number(numerator, denominator, true); }
  [[nodiscard]] std::pair<Number, Number> normalizeDenominatorWith(const Number &) const;

  void simplify();
};
}

namespace std { // NOLINT(cert-dcl58-cpp)

inline Puzzles::Numbers::Number pow(const Puzzles::Numbers::Number &base, const Puzzles::Numbers::Number &exponent) {
  return base.power(exponent);
}

inline string to_string(const Puzzles::Numbers::Number &number) {
  return number.toString();
}

// This doesn't have to be in std, but it must come after to_string, so...
inline std::ostream &operator<<(std::ostream &s, const Puzzles::Numbers::Number &number) {
  s << std::to_string(number);
  return s;
}
}
