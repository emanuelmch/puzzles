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

#include "common/twobitstorage.h"

#include <gtest/gtest.h>

using Puzzles::TwoBitStorage;

TEST(TwoBitStorage, ShouldStartAtZero) {
  TwoBitStorage storage;

  EXPECT_EQ(storage.size(), 0);
}

TEST(TwoBitStorage, PushToEmpty) {
  TwoBitStorage storage;

  storage.push(3);

  EXPECT_EQ(storage.size(), 1);
  EXPECT_EQ(storage[0], 3);
}

TEST(TwoBitStorage, PushMultiple) {
  const auto max = TwoBitStorage::MAX_SIZE;
  TwoBitStorage storage;

  for (size_t i = 0; i < max; ++i)
    storage.push((max - i) % 4);

  EXPECT_EQ(storage.size(), max);
  for (size_t i = 0; i < max; ++i)
    EXPECT_EQ(storage[i], (max - i) % 4) << "Comparison failed on position " << i;
}
