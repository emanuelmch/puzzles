/*
 * Copyright (c) 2021 Emanuel Machado da Silva
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

#include "common/assertions.h"

#include <atomic>

namespace pzl {

template <typename T>
struct shared_ptr {
  explicit shared_ptr(T *object) : raw{object}, counter{raw ? new std::atomic_size_t{1} : nullptr} {}
  shared_ptr(const shared_ptr<T> &o) : raw{o.raw}, counter{o.counter} {
    if (counter) ++*counter;
  }
  ~shared_ptr() { decreaseCounter(); }

  inline void reset() {
    decreaseCounter();
    this->raw = nullptr;
    this->counter = nullptr;
  }

  inline shared_ptr<T> &operator=(const shared_ptr<T> &o) {
    if (this == &o || this->raw == o.raw) return *this;

    auto otherRaw = o.raw;
    auto otherCounter = o.counter;
    ++*otherCounter;

    decreaseCounter(); // This might delete `o` in some edge cases

    this->raw = otherRaw;
    this->counter = otherCounter;

    return *this;
  }

  explicit inline operator bool() const { return raw != nullptr; }
  inline bool operator!=(const shared_ptr &o) const { return raw != o.raw; }

  inline T *operator->() const { return raw; }

private:
  T *raw;
  std::atomic_size_t *counter;

  inline void decreaseCounter() {
    if (!raw) return;

    ensure(counter);
    if (--*counter == 0) {
      delete counter;
      delete raw;
    }
  }
};
}
