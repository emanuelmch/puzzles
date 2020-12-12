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

#include "compat/defs.h"

#include <cstdint> // uint32_t, intmax_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace pzl {

struct Integer {

  using value_t = uint32_t;

  explicit Integer(const std::string &);
  explicit Integer(intmax_t value);

  [[nodiscard]] inline bool positive() const { return _positive; }
  [[nodiscard]] std::string toString() const;

  [[nodiscard]] Integer operator+(const Integer &) const;
  [[nodiscard]] Integer operator-(const Integer &) const;

#ifdef __cpp_lib_three_way_comparison
  [[nodiscard]] inline bool operator==(const Integer &) const = default;
#else
  [[nodiscard]] inline bool operator==(const Integer &o) const {
    return this->_positive == o._positive && this->slices == o.slices;
  }
#endif

private:
  Integer(std::vector<value_t> slices, bool positive)
      : slices(std::move(slices)), _positive(positive || this->slices.empty()) {}

  std::vector<value_t> slices; // Low-endian base-10 storage
  bool _positive;
};
}

namespace std { // NOLINT(cert-dcl58-cpp)

inline string to_string(const pzl::Integer &integer) {
  return integer.toString();
}
}
