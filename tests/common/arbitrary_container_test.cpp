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

#include "common/arbitrary_container.h"

#include <gtest/gtest.h>

using Puzzles::ArbitraryContainer;

TEST(ArbitraryContainer_0b11_32, ShouldStartAtZero) {
  ArbitraryContainer<0b11, 32> storage;

  EXPECT_EQ(storage.size(), 0);
}

TEST(ArbitraryContainer_0b11_32, PushToEmpty) {
  ArbitraryContainer<0b11, 32> storage;

  storage.push(3);

  EXPECT_EQ(storage.size(), 1);
  EXPECT_EQ(storage[0], 3);
}

TEST(ArbitraryContainer_0b11_32, PushMultiple) {
  const auto maxSize = 32;
  ArbitraryContainer<0b11, maxSize> storage;

  for (size_t i = 0; i < maxSize; ++i) {
    storage.push((maxSize - i) % 0b100);
  }

  EXPECT_EQ(storage.size(), maxSize);
  for (size_t i = 0; i < maxSize; ++i)
    EXPECT_EQ(storage[i], (maxSize - i) % 0b100) << "Comparison failed on position " << i;
}

TEST(ArbitraryContainer_0b1_12, PushMultiple) {
  const auto maxSize = 12;
  ArbitraryContainer<0b1, maxSize> storage;

  for (size_t i = 0; i < maxSize; ++i) {
    storage.push((maxSize - 1) % 0b10);
  }

  EXPECT_EQ(storage.size(), maxSize);
  for (size_t i = 0; i < maxSize; ++i) {
    EXPECT_EQ(storage[i], (maxSize - 1) % 0b10) << "Comparison failed on position " << i;
  }
}
