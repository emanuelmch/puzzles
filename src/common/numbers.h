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

#include <cassert>
#include <cstdint>
#include <limits>
#include <string>

namespace Puzzles::Numbers {

inline uint8_t ctoi(char c) {
  assert(c >= '0' && c <= '9');
  return c - '0';
}

inline char itoc(uint8_t i) {
  assert(i < 10);
  return i + '0';
}

inline uintmax_t factorial(uintmax_t value) {
  return (value < 2) ? 1 : value * factorial(value - 1);
}

template <typename Target, typename Input>
inline bool fits(Input value) {
  return value >= std::numeric_limits<Target>::min() && value <= std::numeric_limits<Target>::max();
}

struct Number {

  explicit Number(std::string);
  explicit Number(intmax_t);
  Number(intmax_t, uintmax_t);

  [[nodiscard]] Number operator+(const Number &) const;

  [[nodiscard]] bool operator<(const Number &) const;
  [[nodiscard]] bool operator==(const Number &) const;

  [[nodiscard]] std::string toString() const;

private:
  std::string numerator;
  std::string denominator;
  bool positive;

  Number(uintmax_t, uintmax_t, bool);

  [[nodiscard]] std::pair<Number, Number> normalizeDenominatorWith(const Number &) const;
  void simplify();
};
}

namespace std { // NOLINT(cert-dcl58-cpp)

inline string to_string(const Puzzles::Numbers::Number &number) {
  return number.toString();
}
}
