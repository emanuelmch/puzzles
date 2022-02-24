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

#include "shurikens/model.h"

#include <gtest/gtest.h>

using namespace Shurikens;

using std::array;

TEST(Shuriken, SwapTop) {
  auto shuriken = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});
  auto swapped = shuriken.apply(swap_top);

  array<Cell, 12> cells = {G, H, I, D, E, F, A, B, C, J, K, L};
  EXPECT_EQ(swapped.cells, cells);
}

TEST(Shuriken, SwapBottom) {
  auto shuriken = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});
  auto swapped = shuriken.apply(swap_bottom);

  array<Cell, 12> cells = {A, B, C, J, K, L, G, H, I, D, E, F};
  EXPECT_EQ(swapped.cells, cells);
}

TEST(Shuriken, TurnSideA) {
  auto shuriken = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});
  auto swapped = shuriken.apply(turn_a);

  array<Cell, 12> cells = {F, A, B, C, D, E, G, H, I, J, K, L};
  EXPECT_EQ(swapped.cells, cells);
}

TEST(Shuriken, TurnSideB) {
  auto shuriken = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});
  auto swapped = shuriken.apply(turn_b);

  array<Cell, 12> cells = {A, B, C, D, E, F, L, G, H, I, J, K};
  EXPECT_EQ(swapped.cells, cells);
}

TEST(Shuriken, ReverseSideA) {
  auto shuriken = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});
  auto swapped = shuriken.apply(reverse_a);

  array<Cell, 12> cells = {B, C, D, E, F, A, G, H, I, J, K, L};
  EXPECT_EQ(swapped.cells, cells);
}

TEST(Shuriken, ReverseSideB) {
  auto shuriken = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});
  auto swapped = shuriken.apply(reverse_b);

  array<Cell, 12> cells = {A, B, C, D, E, F, H, I, J, K, L, G};
  EXPECT_EQ(swapped.cells, cells);
}

TEST(Shuriken, PerfectlySolvedShurikenShouldBeSolved) {
  auto shuriken = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});

  EXPECT_TRUE(shuriken.isSolved());
}

TEST(Shuriken, InvertedSolvedShurikenShouldBeSolved) {
  auto shuriken = Shuriken({G, H, I, J, K, L, A, B, C, D, E, F});

  EXPECT_TRUE(shuriken.isSolved());
}

TEST(Shuriken, EqualsAndHash) {
  auto shuriken1 = Shuriken({B, A, C, J, G, F, H, D, K, E, I, L});
  auto shuriken2 = Shuriken({B, A, C, J, G, F, H, D, K, E, I, L});

  EXPECT_EQ(shuriken1, shuriken2);

  auto hash1 = std::hash<Shuriken>()(shuriken1);
  auto hash2 = std::hash<Shuriken>()(shuriken2);

  EXPECT_EQ(hash1, hash2);
}

TEST(Shuriken, EqualsAndHashDontConsiderBothSidesDifferent) {
  auto shuriken1 = Shuriken({A, B, C, D, E, F, G, H, I, J, K, L});
  auto shuriken2 = Shuriken({G, H, I, J, K, L, A, B, C, D, E, F});

  EXPECT_EQ(shuriken1, shuriken2);

  auto hash1 = std::hash<Shuriken>()(shuriken1);
  auto hash2 = std::hash<Shuriken>()(shuriken2);

  EXPECT_EQ(hash1, hash2);
}
