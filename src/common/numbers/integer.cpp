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
  if (slices.empty() || o.slices.empty()) return Integer{0};

  auto min = this->absolute();
  auto max = o.absolute();

  if (compareSlices(this->slices, o.slices) == compat::strong_ordering::greater) {
    std::swap(min, max);
  }

  Integer result{0};
  for (Integer i{0}; i < min; ++i) {
    result += max;
  }

  result._positive = this->positive() == o.positive();
  return result;
}

Integer Integer::operator/(const Integer &o) const {
  ensure(o != 0); // division by zero is undefined

  if (slices.empty()) { // Zero divided by anything is always zero
    return *this;
  }

  // if (this < o) then (this / o) will be a fraction, which we don't support
  ensure_m(o.absolute() <= this->absolute(),
           "this is [" << std::to_string(*this) << "], o is [" << std::to_string(o) << "]");

  // Now for the actual division implementation
  Integer remainder{this->slices, true};
  Integer result{0};

  if (o.slices.size() == 1) {
    // Optimizing this common scenario
    auto base = o.slices[0];
    std::vector<std::pair<intmax_t, intmax_t>> stepSizes;
    stepSizes.emplace_back(1, base);

    constexpr auto max = std::numeric_limits<intmax_t>::max() / 2;
    for (intmax_t i = 2; i <= max && (*this > stepSizes.back().second); i *= 2) {
      stepSizes.emplace_back(i, i * base);
    }

    for (auto it = stepSizes.crbegin(); it != stepSizes.crend(); ++it) {
      auto [i, stepSize] = *it;
      Integer step{stepSize};
      while (step <= remainder) {
        remainder -= step;
        result = result + i;
        ensure(remainder.positive()); // We don't support fractions, to we should always stop exactly at 0
      }
    }
  } else {
    auto step = o.absolute();

    while (!remainder.slices.empty()) {
      remainder -= step;
      ++result;
      ensure(remainder.positive()); // We don't support fractions, to we should always stop exactly at 0
    }
  }

  result._positive = this->positive() == o.positive() || result.slices.empty();
  return result;
}

Integer Integer::operator%(const Integer &o) const {
  ensure(o != 0); // division by zero is undefined

  if (slices.empty()) { // Zero divided by anything is always zero
    return *this;
  }

  Integer remainder{this->slices, true};

  if (o.slices.size() == 1) {
    // Optimizing this common scenario
    auto base = o.slices[0];
    std::vector<intmax_t> stepSizes;
    stepSizes.push_back(base);

    constexpr auto max = std::numeric_limits<intmax_t>::max() / 2;
    for (intmax_t i = 2; i <= max && (*this > stepSizes.back()); i *= 2) {
      stepSizes.push_back(i * base);
    }

    for (auto it = stepSizes.crbegin(); it != stepSizes.crend(); ++it) {
      auto stepSize = *it;
      Integer step{stepSize};
      while (step <= remainder) {
        remainder -= stepSize;
      }
    }
  } else {
    auto step = o.absolute();
    while (step <= remainder) {
      remainder -= step;
    }
  }

  remainder._positive = this->positive() == o.positive() || remainder.slices.empty();
  return remainder;
}

Integer Integer::operator+(intmax_t value) const {
  if (value == 0) return *this;
  if (slices.empty()) return Integer{value};

  auto sameSign = (value >= 0 && this->positive()) || (value < 0 && !this->positive());
  auto absValue = std::abs(value);
  if (sameSign && absValue + slices[0] < 1000000000) {
    Integer result{*this};
    result.slices[0] += absValue;
    return result;
  }

  return *this + Integer{value};
}

Integer Integer::operator*(intmax_t value) const {
  switch (value) {
  case 0:
    return Integer{0};
  case 1:
    return *this;
  case -1:
    return Integer{slices, !_positive};
  default:
    return *this * Integer(value);
  }
}

Integer Integer::power(const Integer &exponent) const {
  ensure(*this != 0 || exponent != 0); // zero ^ zero is undefined
  ensure(exponent.positive());         // Haven't implemented this yet

  Integer result{1};

  for (Integer i{0}; i < exponent; ++i) {
    result *= *this;
  }

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

Integer &Integer::operator++() {
  if (slices.empty()) {
    slices.push_back(1);
    return *this;
  }

  if (positive()) {
    auto it = slices.begin();

    while (it != slices.end()) {
      if (*it == SLICE_MAX) {
        *it = 0;
        ++it;
      } else {
        ++(*it);
        return *this;
      }
    }

    slices.push_back(1);
    return *this;
  }

  if (slices[0] > 1) {
    --slices[0];
    return *this;
  }

  if (slices.size() == 1) {
    slices.clear();
    _positive = true;
    return *this;
  }

  auto it = slices.begin();
  while (it != slices.end()) {
    if (*it == 0) {
      *it = SLICE_MAX;
      ++it;
    } else {
      --(*it);
      return *this;
    }
  }

  slices.pop_back();
  return *this;
}
