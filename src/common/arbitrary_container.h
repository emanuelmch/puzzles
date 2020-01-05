/*
 * Copyright (c) 2019 Emanuel Machado da Silva
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
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Puzzles {

typedef size_t value_t;

static constexpr inline size_t calculateValueBitLength(size_t value) {
  assert(value > 0);
  assert(value <= 0b11111111); // No real reason to stop there, I just haven't tested any further

  auto digits = 0;
  size_t next = 1;
  while (value > 0) {
    digits++;

    if (next >= value) break;

    value = value - next;
    next = next * 2;
  }

  return digits;
}

template <value_t MAX_VALUE> struct ArbitraryContainer {

  const size_t valueBitLength = calculateValueBitLength(MAX_VALUE);

  // Constructors
  ArbitraryContainer() = default;
  ArbitraryContainer(const ArbitraryContainer<MAX_VALUE>&) = default;

  inline void push(value_t value) {
    assert(value <= MAX_VALUE);

    std::vector<bool> results;
    while (value > 0) {
      results.push_back(value % 2);
      value = value / 2;
    }

    for (size_t i = 0; i < (valueBitLength - results.size()); ++i) {
      internal.push_back(0);
    }

    for (auto it = results.rbegin(); it != results.rend(); ++it) {
      internal.push_back(*it);
    }

    _size++;
  }

  inline value_t at(size_t index) const {
    assert(index < _size);

    value_t result = 0;
    auto start = index * valueBitLength;

    for (size_t i = 0; i < valueBitLength; ++i) {
      if (internal[start + i]) {
        result += std::pow(2, valueBitLength - 1 - i);
      }
    }

    return result;
  }
  inline value_t operator[](size_t i) const { return at(i); }
  inline size_t size() const { return _size; }

  // TODO: Replace this with real iterators
  explicit inline operator std::vector<uint8_t>() const {
    std::vector<uint8_t> result;
    result.reserve(_size);

    for (size_t i = 0; i < _size; ++i) {
      uint8_t value = (*this)[i];
      result.push_back(value);
    }

    return result;
  }

  // Operators
  inline ArbitraryContainer<MAX_VALUE> &operator=(const ArbitraryContainer<MAX_VALUE> &other) {
    internal = other.internal;
    _size = other._size;
    return *this;
  }

private:
  std::vector<bool> internal;
  size_t _size = 0;
};
}
