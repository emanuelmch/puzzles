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

#include "common/assertions.h"

#include <cstdlib>
#include <iterator>

#if __has_include(<coroutine>)
#include <coroutine>
#endif

#if __has_include(<version>)
#include <version>
#endif

#if defined(__cpp_impl_coroutine)

namespace Puzzles {

// TODO: Properly test non-infinite sequences
template <typename T>
struct LazySequence {
  struct promise_type {
    T lastYieldedValue;

    constexpr auto initial_suspend() noexcept { return std::suspend_always(); }
    constexpr auto final_suspend() noexcept { return std::suspend_always(); }
    constexpr auto get_return_object() noexcept { return LazySequence(*this); }
    constexpr auto unhandled_exception() noexcept { std::exit(1); }
    constexpr auto yield_value(const T value) noexcept {
      lastYieldedValue = value;
      return std::suspend_always();
    }
  };

  struct iterator {

    // std::iterator_traits
    using difference_type = size_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::input_iterator_tag;

    explicit constexpr iterator(const std::coroutine_handle<promise_type> *handle) : handle(handle) {}

    constexpr bool operator!=(const iterator &o) const { return handle != o.handle; }

    constexpr T operator*() {
      ensure_m(handle != nullptr, "Tried to dereference the end() of a LazySequence");

      if (value == nullptr) {
        ensure(!handle->done());
        handle->resume();
        value = &(handle->promise().lastYieldedValue);
      }
      return *value;
    }

    constexpr iterator *operator++() {
      if (value == nullptr) {
        ensure(!handle->done());
        // Let's skip the current value
        handle->resume();
      } else {
        value = nullptr;
      }
      return this;
    }

  private:
    const std::coroutine_handle<promise_type> *handle;
    T *value = nullptr;
  };

  std::coroutine_handle<promise_type> handle;

  explicit constexpr LazySequence(promise_type &handle)
      : handle(std::coroutine_handle<promise_type>::from_promise(handle)) {}
  constexpr LazySequence(const LazySequence<T> &) = delete;
  constexpr ~LazySequence() {
    if (handle) handle.destroy();
  }

  constexpr iterator begin() const { return iterator(&handle); }
  constexpr iterator end() const { return iterator(nullptr); }
};
}

#else // defined(__cpp_impl_coroutine)

namespace Puzzles {

template <typename T>
struct LazySequence {};
}

#endif // defined(__cpp_impl_coroutine)
