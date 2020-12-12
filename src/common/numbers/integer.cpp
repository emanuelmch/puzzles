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
#include "compat/compare.h"    // compat::strong_ordering, compat::compare

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

inline compat::strong_ordering compareSlices(const std::vector<Integer::value_t> &left,
                                             const std::vector<Integer::value_t> &right) {
  auto lengthComparison = compat::compare(left.size(), right.size());
  if (lengthComparison != compat::strong_ordering::equal) {
    return lengthComparison;
  }

  auto lit = left.crbegin(), rit = right.crbegin();
  while (lit != left.crend()) {
    ensure(rit != right.crend());

    auto sliceComparison = compat::compare(*lit, *rit);
    if (sliceComparison == compat::strong_ordering::equal) {
      ++lit;
      ++rit;
      continue;
    }

    return sliceComparison;
  }

  return compat::strong_ordering::equal;
}

Integer Integer::operator+(const Integer &o) const {
  if (slices.empty()) return o;
  if (o.slices.empty()) return *this;

  auto sameSign = this->positive() == o.positive();
  if (!sameSign && this->slices == o.slices) {
    return Integer(0);
  }

  bool finalSign;
  typeof(slices.cbegin()) lit, rit;
  typeof(slices.cend()) lend, rend;

  // if sameSign, we don't care about the order, so we can avoid the compareSlices call
  if (sameSign || compareSlices(this->slices, o.slices) != compat::strong_ordering::less) {
    finalSign = this->_positive;
    lit = this->slices.cbegin();
    lend = this->slices.cend();

    rit = o.slices.cbegin();
    rend = o.slices.cend();
  } else {
    finalSign = o._positive;
    lit = o.slices.cbegin();
    lend = o.slices.cend();

    rit = this->slices.cbegin();
    rend = this->slices.cend();
  }

  std::vector<value_t> result;
  result.reserve(std::max(this->slices.size(), o.slices.size()) + 1);

  int_fast64_t carryOver = 0;

  while (lit != lend || rit != rend) {
    int_fast64_t lbit = lit == lend ? 0 : valueAndAdvance<value_t>(&lit);
    int_fast64_t rbit = rit == rend ? 0 : valueAndAdvance<value_t>(&rit);
    int_fast64_t sum = sameSign ? lbit + rbit + carryOver : lbit - rbit - carryOver;

    ensure(sum >= (SLICE_SIZE * static_cast<intmax_t>(-1)) && sum <= (SLICE_SIZE * 2 - 1));

    if (sum < 0) {
      carryOver = 1;
      sum += SLICE_SIZE;
    } else if (sum > SLICE_MAX) {
      carryOver = 1;
      sum -= SLICE_SIZE;
    } else {
      carryOver = 0;
    }

    result.push_back(sum);
  }

  ensure_m(carryOver == 0 || (carryOver == 1 && sameSign), "carry over is " << carryOver);
  if (carryOver) result.push_back(1);

  while (result.back() == 0) {
    result.pop_back();
    ensure_m(!result.empty(), "sum is 0, but we should've left the function at the beginning");
  }

  return Integer(result, finalSign);
}

Integer Integer::operator-(const Integer &o) const {
  if (this->slices.empty()) return Integer{o.slices, !o._positive};
  if (*this == o) return Integer{0};

  if (this->positive() == o.positive() && o.slices.size() == 1 && o.slices[0] <= this->slices[0]) {
    // Optimizing this common scenario
    Integer newInteger{*this};
    newInteger.slices[0] -= o.slices[0];
    return newInteger;
  }

  return *this + Integer{o.slices, !o._positive};
}

Integer Integer::operator*(const Integer &o) const {
  auto min = this->absolute();
  auto max = o.absolute();

  if (compareSlices(this->slices, o.slices) == compat::strong_ordering::greater) {
    std::swap(min, max);
  }

  Integer result{0};
  // TODO: Replace with ++i
  for (Integer i{0}; i < min; i = i + Integer{1}) {
    // TODO: Replace with result += max
    result = result + max;
  }

  result._positive = this->positive() == o.positive();
  return result;
}

Integer Integer::operator/(const Integer &o) const {
  // TODO: Replace with o != 0
  ensure(o != Integer{0}); // division by zero is undefined

  if (slices.empty()) { // Zero divided by anything is always zero
    return *this;
  }

  ensure(o <= *this); // if (this < o) then (this / o) will be a fraction, which we don't support

  // Now for the actual division implementation
  Integer remainder{this->slices, true};
  Integer result{0};

  while (!remainder.slices.empty()) {
    // TODO: Replace with remainder -= o
    remainder = remainder - o;
    // TODO: Replace with ++result
    result = result + Integer{1};
    ensure(remainder.positive()); // We don't support fractions, to we should always stop exactly at 0
  }

  result._positive = this->positive() == o.positive();
  return result;
}

bool Integer::operator<(const Integer &o) const {
  if (this->positive() != o.positive()) {
    return this->positive() < o.positive();
  }

  auto sliceComparison = compareSlices(this->slices, o.slices);
  if (this->positive()) {
    return sliceComparison == compat::strong_ordering::less;
  } else {
    return sliceComparison == compat::strong_ordering::greater;
  }
}

bool Integer::operator<=(const Integer &o) const {
  if (this->positive() != o.positive()) {
    return this->positive() < o.positive();
  }

  auto bitComparison = compareSlices(this->slices, o.slices);
  if (this->positive()) {
    return bitComparison != compat::strong_ordering::greater;
  } else {
    return bitComparison != compat::strong_ordering::less;
  }
}
