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

#pragma once

#include "common/numbers/integer.h"

#include <cstdint> // intmax_t
#include <string>
#include <tuple>
#include <utility> // std::move

namespace pzl {

struct Rational {

  explicit Rational(const std::string &value) : numerator{value}, denominator{1} {}

  explicit Rational(intmax_t value) : numerator{value}, denominator{1} {}
  Rational(intmax_t numerator, intmax_t denominator);

  explicit Rational(pzl::Integer numerator) : numerator{std::move(numerator)}, denominator{1} {}
  Rational(pzl::Integer numerator, const pzl::Integer &denominator);

  [[nodiscard]] Rational operator+(const Rational &) const;
  [[nodiscard]] Rational operator-(const Rational &) const;
  [[nodiscard]] Rational operator*(const Rational &) const;
  [[nodiscard]] Rational operator/(const Rational &) const;

  [[nodiscard]] Rational power(const Rational &exponent) const;

  void operator+=(const Rational &o) { *this = *this + o; }
  void operator-=(const Rational &o) { *this = *this - o; }
  void operator*=(const Rational &o) { *this = *this * o; }

  [[nodiscard]] bool operator<(const Rational &) const;
  // TODO: <= Could be more efficient
  [[nodiscard]] inline bool operator<=(const Rational &o) const { return *this < o || *this == o; }
  [[nodiscard]] inline bool operator>=(const Rational &o) const { return o < *this; }
  [[nodiscard]] bool operator==(const Rational &) const;

  [[nodiscard]] inline bool operator==(intmax_t o) const { return this->denominator == 1 && this->numerator == o; }
  [[nodiscard]] inline bool operator!=(intmax_t o) const { return !(*this == o); }

  [[nodiscard]] std::string toString() const;
  [[nodiscard]] std::string toStringWithDecimalExpansion() const;

private:
  pzl::Integer numerator;
  pzl::Integer denominator;

  inline Rational &copy(const Rational &o) {
    this->numerator = o.numerator;
    this->denominator = o.denominator;
    return *this;
  }

  [[nodiscard]] std::tuple<pzl::Integer, pzl::Integer, pzl::Integer> normalizeDenominatorWith(const Rational &) const;
  [[nodiscard]] inline bool positive() const { return numerator.positive(); }

  Rational &simplify();
};
}

namespace std { // NOLINT(cert-dcl58-cpp)

inline pzl::Rational pow(const pzl::Rational &base, const pzl::Rational &exponent) {
  return base.power(exponent);
}

inline string to_string(const pzl::Rational &rational) {
  return rational.toString();
}

// This doesn't have to be in std, but it does have to come after to_string, so...
inline std::ostream &operator<<(std::ostream &s, const pzl::Rational &rational) {
  s << std::to_string(rational);
  return s;
}
}
