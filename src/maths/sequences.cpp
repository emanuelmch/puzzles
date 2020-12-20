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

#include "sequences.h"

#include "maths/primes.h"

#include <cstdint>

#if __has_include(<version>)
#include <version>
#endif

#if defined(__cpp_impl_coroutine)

#include <algorithm>
#include <cinttypes>
#include <execution>
#include <string>

using namespace Maths;

Puzzles::LazySequence<uintmax_t> Sequences::emirps() {
  for (uintmax_t i = 0;; ++i) {
    if (isPrime(i)) {
      std::string string = std::to_string(i);
      std::reverse(string.begin(), string.end());
      auto reversed = std::strtoumax(string.c_str(), nullptr, 10);
      if (i != reversed && isPrime(reversed)) {
        co_yield i;
      }
    }
  }
}

Puzzles::LazySequence<uintmax_t> Sequences::highlyCompositeNumbers() {
  auto lastCount = 0u;

  for (auto number = 0u;; ++number) {
    auto range = std::views::iota(1u, number + 1);
    auto count = std::count_if(range.begin(), range.end(), [number](auto i) { return number % i == 0; });
    if (count > lastCount) {
      co_yield number;
      lastCount = count;
    }
  }
}

#else // defined(__cpp_impl_coroutine)

Puzzles::LazySequence<uintmax_t> Maths::Sequences::emirps() {
  return Puzzles::LazySequence<uintmax_t>();
}

Puzzles::LazySequence<uintmax_t> Maths::Sequences::highlyCompositeNumbers() {
  return Puzzles::LazySequence<uintmax_t>();
}

#endif // defined(__cpp_impl_coroutine)
