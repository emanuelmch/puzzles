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
#include <sys/types.h>
#include <vector>

namespace Puzzles {

typedef size_t value_t;

template <value_t MAX_VALUE, size_t MAX_SIZE> struct ArbitraryContainer {

  ArbitraryContainer() : internal(0), _size(0) {
    static_assert(MAX_VALUE <= 0b11);
    static_assert(MAX_SIZE <= 32);
  }

  inline void push(value_t value) {
    assert(value <= MAX_VALUE);
    assert(_size < MAX_SIZE);

    _size++;
    // FIXME: This only works when MAX_VALUE <= 0b11
    auto shift = (MAX_SIZE - _size) * 2;
    internal += static_cast<u_int64_t>(value) << shift;
  }

  inline value_t at(size_t i) const {
    assert(i < _size);
    // FIXME: This only works when MAX_VALUE <= 0b11
    auto shift = (MAX_SIZE - 1 - i) * 2;
    return (internal & (static_cast<u_int64_t>(0b11) << shift)) >> shift;
  }
  inline value_t operator[](size_t i) const { return at(i); }
  inline size_t size() const { return _size; }

  // TODO: Replace this with real iterators
  explicit inline operator std::vector<u_int8_t>() const {
    std::vector<u_int8_t> result;
    result.reserve(_size);

    for (size_t i = 0; i < _size; ++i) {
      u_int8_t value = (*this)[i];
      result.push_back(value);
    }

    return result;
  }

private:
  u_int64_t internal;
  size_t _size;
};
}
