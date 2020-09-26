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

namespace Puzzles {

template <typename Iterator1, typename Iterator2>
struct ZipIterator {

  struct iterator {
    iterator(Iterator1 first, Iterator2 second) : first(first), second(second) {}

    bool operator!=(const iterator &o) const { return first != o.first && second != o.second; }

    iterator *operator++() {
      std::advance(first, 1);
      std::advance(second, 1);
      return this;
    }

    auto operator*() { return std::make_pair(*first, *second); }

  private:
    Iterator1 first;
    Iterator2 second;
  };

  ZipIterator(const Iterator1 firstBegin, const Iterator1 firstEnd, const Iterator2 secondBegin,
              const Iterator2 secondEnd)
      : it_begin(firstBegin, secondBegin), it_end(firstEnd, secondEnd) {}

  iterator begin() const { return it_begin; }
  iterator end() const { return it_end; }

private:
  const iterator it_begin;
  const iterator it_end;
};

template <typename Iterable, typename Iterable2>
constexpr ZipIterator<typename Iterable::iterator, typename Iterable2::iterator> zip(const Iterable &first,
                                                                                     const Iterable2 &second) {
  return ZipIterator(std::begin(first), std::end(first), std::begin(second), std::end(second));
}
}
