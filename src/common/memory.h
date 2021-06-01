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
struct MemoryCounters {
  T *const raw;
  std::atomic_size_t strong;
  std::atomic_size_t weak;

  explicit MemoryCounters(T *raw) : raw{raw}, strong{1}, weak{0} { ensure(raw != nullptr); }

  inline void increaseStrong() { ++strong; }
  inline void decreaseStrong() {
    if (--strong == 0) {
      delete raw;
      if (weak == 0) {
        delete this;
      }
    }
  }

  inline void increaseWeak() { ++weak; }
  inline void decreaseWeak() {
    if (--weak == 0 && strong == 0) {
      delete this;
    }
  }
};

template <typename T>
struct weak_ptr; // forward declaration so we can have it be a friend of shared_ptr<T>

template <typename T>
struct shared_ptr {
  explicit shared_ptr(nullptr_t) : counters{nullptr} {}
  explicit shared_ptr(T *raw) : counters{new MemoryCounters{raw}} {}

  shared_ptr(const shared_ptr<T> &o) : counters{o.counters} {
    if (counters) counters->increaseStrong();
  }
  ~shared_ptr() {
    if (counters) counters->decreaseStrong();
  }

  inline void reset() {
    if (counters) {
      counters->decreaseStrong();
      counters = nullptr;
    }
  }

  inline shared_ptr<T> &operator=(const shared_ptr<T> &o) {
    if (this == &o || this->counters == o.counters) return *this;

    auto otherCounters = o.counters;
    if (otherCounters) otherCounters->increaseStrong();

    if (this->counters) this->counters->decreaseStrong();

    this->counters = otherCounters;

    return *this;
  }

  inline explicit operator bool() const { return counters != nullptr; }
  inline bool operator!=(const shared_ptr &o) const { return counters != o.counters; }

  inline T *operator->() const { return counters->raw; }

  friend weak_ptr<T>;

private:
  MemoryCounters<T> *counters;
};

template <typename T>
struct weak_ptr {

  explicit weak_ptr(nullptr_t) : counters{nullptr} {}
  weak_ptr(const shared_ptr<T> &o) : counters{o.counters} { // NOLINT(google-explicit-constructor)
    counters->increaseWeak();
  }
  ~weak_ptr() { if (counters) counters->decreaseWeak(); }

  inline bool expired() { return counters == nullptr || counters->strong == 0; }

private:
  MemoryCounters<T> *counters;
};

template <typename T, typename... Args>
inline shared_ptr<T> make_shared(Args &&...args) {
  return shared_ptr<T>(new T(args...));
}
}
