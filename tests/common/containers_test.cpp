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

#include "common/containers.h"

#include <gtest/gtest.h>

TEST(GenerateArray, Simple) {
  auto generator = []() { return 1u; };

  std::array<unsigned int, 3> array = pzl::generate_array<3>(generator);

  ASSERT_EQ(array.size(), 3);
  EXPECT_EQ(array[0], 1);
  EXPECT_EQ(array[1], 1);
  EXPECT_EQ(array[2], 1);
}

TEST(GenerateArray, Order) {
  int value = 200;
  auto generator = [&value]() { return value++; };

  std::array<int, 3> array = pzl::generate_array<3>(generator);

  ASSERT_EQ(array.size(), 3);
  EXPECT_EQ(array[0], 200);
  EXPECT_EQ(array[1], 201);
  EXPECT_EQ(array[2], 202);
}

TEST(GenerateArrayIndexed, Simple) {
  auto generator = [](size_t i) { return int(i * i); };

  std::array<int, 5> array = pzl::generate_array_indexed<5>(generator);

  ASSERT_EQ(array.size(), 5);
  EXPECT_EQ(array[0], 0);
  EXPECT_EQ(array[1], 1);
  EXPECT_EQ(array[2], 4);
  EXPECT_EQ(array[3], 9);
  EXPECT_EQ(array[4], 16);
}

TEST(GenerateArrayIota, Simple) {
  std::array<size_t, 5> array = pzl::generate_array_iota<5>();

  ASSERT_EQ(array.size(), 5);
  EXPECT_EQ(array[0], 0);
  EXPECT_EQ(array[1], 1);
  EXPECT_EQ(array[2], 2);
  EXPECT_EQ(array[3], 3);
  EXPECT_EQ(array[4], 4);
}

TEST(GenerateArrayIota, Simple_WithType) {
  std::array<int, 5> array = pzl::generate_array_iota<5, int>();

  ASSERT_EQ(array.size(), 5);
  EXPECT_EQ(array[0], 0);
  EXPECT_EQ(array[1], 1);
  EXPECT_EQ(array[2], 2);
  EXPECT_EQ(array[3], 3);
  EXPECT_EQ(array[4], 4);
}
