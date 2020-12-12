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

#include "integer.h"

#include "common/assertions.h" // ensure
#include "common/strings.h"    // Puzzles::padLeading

#include <cmath> // std::pow

using pzl::Integer;

constexpr Integer::value_t SLICE_MAX = 999999999;
constexpr Integer::value_t SLICE_SIZE = SLICE_MAX + 1;

template <typename value_t, typename iterator>
inline value_t valueAndAdvance(iterator *it) {
  value_t value = **it;
  std::advance(*it, 1);
  return value;
}

Integer::Integer(const std::string &value) : _positive(value.empty() || value[0] != '-') {
  if (value.empty() || value == "0") {
    ensure(_positive); // Can't have negative zero
    return;
  }

  std::string_view offset{value};
  if (offset[0] == '-') {
    offset = offset.substr(1);
  }
  ensure(offset.substr(1).find_first_not_of("0123456789") == value.npos);

  auto it = offset.crbegin();
  while (it != offset.crend()) {
    uint_fast32_t result = 0;
    for (auto i = 0; i < 9; ++i) {
      if (it != offset.crend()) {
        auto digit = valueAndAdvance<char>(&it) - '0';
        result += digit * std::pow(10, i);
      }
    }
    this->slices.push_back(result);
  }
}

Integer::Integer(intmax_t value) : _positive(value >= 0) {
  value = std::abs(value);
  while (value > 0) {
    auto slice = value % static_cast<value_t>(SLICE_SIZE);
    slices.push_back(static_cast<uintmax_t>(slice));
    value = (value - slice) / SLICE_SIZE;
  }
  slices.shrink_to_fit();
}

std::string Integer::toString() const {
  if (slices.empty()) {
    ensure(_positive);
    return "0";
  }

  std::string result;
  for (auto slice : slices) {
    auto nextSlice = std::to_string(slice);
    auto paddedSlice = Puzzles::padLeading(nextSlice, 9, '0');
    result.insert(0, paddedSlice);
  }

  result = Puzzles::trimLeading(result, '0');

  if (!_positive) {
    result.insert(0, 1, '-');
  }

  return result;
}
