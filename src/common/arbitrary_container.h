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
  explicit ArbitraryContainer(size_t count) : internal(count * valueBitLength, 0) { }

  ArbitraryContainer(std::initializer_list<value_t> values) {
    reserve(values.size());
    for (auto value : values) {
      push(value);
    }
  }

  // Capacity
  inline void reserve(size_t new_cap) { internal.reserve(new_cap * valueBitLength); }
  inline void shrink_to_fit() { internal.shrink_to_fit(); }

  // Insertion
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
  }

  // Retrieval
  inline value_t at(size_t index) const {
    assert(index < size());

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
  inline size_t size() const { return internal.size() / valueBitLength; }

  // Iterators
  struct const_iterator {

    const_iterator(const ArbitraryContainer<MAX_VALUE> *container, size_t position)
        : container(container), position(position) {}

    inline bool operator!=(const const_iterator &o) const { return container != o.container || position != o.position; }

    inline const_iterator *operator++() {
      position++;
      return this;
    }

    inline value_t operator*() const {
      assert(position < container->size());
      return container->at(position);
    }

  private:
    const ArbitraryContainer<MAX_VALUE> *container;
    size_t position;
  };

  inline const_iterator begin() const { return const_iterator(this, 0); }
  inline const_iterator end() const { return const_iterator(this, size()); }

  // Operators
  inline ArbitraryContainer<MAX_VALUE> &operator=(const ArbitraryContainer<MAX_VALUE> &other) {
    internal = other.internal;
    return *this;
  }

  inline bool operator<(const ArbitraryContainer<MAX_VALUE> &o) const {
    auto size = internal.size();
    auto otherSize = o.internal.size();

    if (size != otherSize) {
      return size < otherSize;
    }

    for (size_t i = 0; i < size; ++i) {
      if (internal[i] != o.internal[i]) {
        return internal[i] < o.internal[i];
      }
    }
    return false;
  }

private:
  std::vector<bool> internal;
};
}
