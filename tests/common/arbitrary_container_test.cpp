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
using Puzzles::calculateValueBitLength;

TEST(ArbitraryContainer, ValueBitLength) {
  EXPECT_EQ(calculateValueBitLength(0b1), 1);
  EXPECT_EQ(calculateValueBitLength(0b10), 2);
  EXPECT_EQ(calculateValueBitLength(0b11), 2);
  EXPECT_EQ(calculateValueBitLength(0b100), 3);
  EXPECT_EQ(calculateValueBitLength(0b111), 3);
  EXPECT_EQ(calculateValueBitLength(0b1000), 4);
  EXPECT_EQ(calculateValueBitLength(0b1111), 4);
  EXPECT_EQ(calculateValueBitLength(0b10000), 5);
  EXPECT_EQ(calculateValueBitLength(0b11111), 5);
  EXPECT_EQ(calculateValueBitLength(0b100000), 6);
  EXPECT_EQ(calculateValueBitLength(0b111111), 6);
  EXPECT_EQ(calculateValueBitLength(0b1000000), 7);
  EXPECT_EQ(calculateValueBitLength(0b1111111), 7);
  EXPECT_EQ(calculateValueBitLength(0b10000000), 8);
  EXPECT_EQ(calculateValueBitLength(0b11111111), 8);
}

TEST(ArbitraryContainer, ShouldStartAtZero) {
  ArbitraryContainer<0b11> storage;

  EXPECT_EQ(storage.size(), 0);
}

TEST(ArbitraryContainer, ConstructingWithInitialValues) {
  ArbitraryContainer<0b11> storage({0, 1, 2});

  EXPECT_EQ(storage.size(), 3);
  EXPECT_EQ(storage[0], 0);
  EXPECT_EQ(storage[1], 1);
  EXPECT_EQ(storage[2], 2);
}

TEST(ArbitraryContainer, PushToEmpty) {
  ArbitraryContainer<0b11> storage;

  storage.push(3);

  EXPECT_EQ(storage.size(), 1);
  EXPECT_EQ(storage[0], 3);
}

TEST(ArbitraryContainer, PushMultiple_0b1) {
  const auto maxSize = 256;
  const auto maxValue = 0b1;
  ArbitraryContainer<maxValue> storage;

  for (size_t i = 0; i < maxSize; ++i) {
    storage.push((maxSize - 1) % (maxValue + 1));
  }

  EXPECT_EQ(storage.size(), maxSize);
  for (size_t i = 0; i < maxSize; ++i) {
    EXPECT_EQ(storage[i], (maxSize - 1) % (maxValue + 1)) << "Comparison failed on position " << i;
  }
}

TEST(ArbitraryContainer, PushMultiple_0b11) {
  const auto maxSize = 256;
  const auto maxValue = 0b11;
  ArbitraryContainer<maxValue> storage;

  for (size_t i = 0; i < maxSize; ++i) {
    storage.push((maxSize - i) % (maxValue + 1));
  }

  EXPECT_EQ(storage.size(), maxSize);
  for (size_t i = 0; i < maxSize; ++i)
    EXPECT_EQ(storage[i], (maxSize - i) % (maxValue + 1)) << "Comparison failed on position " << i;
}

TEST(ArbitraryContainer, PushMultiple0b11111111) {
  const auto maxSize = 256;
  const auto maxValue = 0b11111111;
  ArbitraryContainer<maxValue> storage;

  for (size_t i = 0; i < maxSize; ++i) {
    storage.push((maxSize - 1) % (maxValue + 1));
  }

  EXPECT_EQ(storage.size(), maxSize);
  for (size_t i = 0; i < maxSize; ++i) {
    EXPECT_EQ(storage[i], (maxSize - 1) % (maxValue + 1)) << "Comparison failed on position " << i;
  }
}

TEST(ArbitraryContainer, LessThan_SameObjects) {
  const ArbitraryContainer<0b11> storage0({0, 1});
  const ArbitraryContainer<0b11> storage1({0, 1});

  EXPECT_FALSE(storage0 < storage1);
  EXPECT_FALSE(storage1 < storage0);
}

TEST(ArbitraryContainer, LessThan_DifferentSizes) {
  const ArbitraryContainer<0b11> storage0({0, 1});
  const ArbitraryContainer<0b11> storage1({0, 1, 2});

  EXPECT_TRUE(storage0 < storage1);
  EXPECT_FALSE(storage1 < storage0);
}

TEST(ArbitraryContainer, LessThan_DifferentValues) {
  const ArbitraryContainer<0b11> storage0({0, 1, 1});
  const ArbitraryContainer<0b11> storage1({0, 1, 2});

  EXPECT_TRUE(storage0 < storage1);
  EXPECT_FALSE(storage1 < storage0);
}
