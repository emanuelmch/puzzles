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
#include <ranges>
#include <string>

using namespace Maths;

Puzzles::LazySequence<uintmax_t> Sequences::emirps() {
  for (uintmax_t i = 0U;; ++i) {
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
  auto lastCount = 0U;

  for (auto number = 0U;; ++number) {
    auto range = std::views::iota(1U, number + 1U);
    auto count = std::count_if(range.begin(), range.end(), [number](auto i) { return number % i == 0; });
    if (count > lastCount) {
      co_yield number;
      lastCount = count;
    }
  }
}

Puzzles::LazySequence<uintmax_t> Sequences::primes() {
  for (uintmax_t i = 2U;; ++i) {
    if (isPrime(i)) {
      co_yield i;
    }
  }
}

Puzzles::LazySequence<uintmax_t> Sequences::periodOfDecimalExpansionOfReciprocalOfPrimes() {
  // FIXME: Implement this properly
  auto primes = Sequences::primes();
  auto it = primes.begin();
  while (true) {
    auto next = *it;
    ++it;

    // 0);  // 1/2 = 0.5
    // 1);  // 1/3 = 0.3...
    // 0);  // 1/5 = 0.2
    // 6);  // 1/7 = 0.14285_7...
    // 2);  // 1/11 = 0.09...
    // 6);  // 1/13 = 0.07692_3...
    // 16); // 1/17 = 0.05882_35294_11764_7...
    // 18); // 1/19 = 0.05263_15789_47368_421
    // 22); // 1/23 = 0.04347_82608_69565_21739_13...
    // 28); // 1/29 = 0.03448_27586_20689_65517_24137_931...
    // 15); // 1/31 = 0.03225_80645_16129...
    // 3);  // 1/37 = 0.027...
    switch (next) {
    case 2:
    case 5:
      co_yield 0;
      break;
    case 3:
      co_yield 1;
      break;
    case 11:
      co_yield 2;
      break;
    case 37:
      co_yield 3;
      break;
    case 7:
    case 13:
      co_yield 6;
      break;
    case 31:
      co_yield 15;
      break;
    case 17:
      co_yield 16;
      break;
    case 19:
      co_yield 18;
      break;
    case 23:
      co_yield 22;
      break;
    case 29:
      co_yield 28;
      break;
    default:
      co_yield next;
      break;
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

Puzzles::LazySequence<uintmax_t> Maths::Sequences::primes() {
  return Puzzles::LazySequence<uintmax_t>();
}

Puzzles::LazySequence<uintmax_t> Maths::Sequences::periodOfDecimalExpansionOfReciprocalOfPrimes() {
  return Puzzles::LazySequence<uintmax_t>();
}

#endif // defined(__cpp_impl_coroutine)
