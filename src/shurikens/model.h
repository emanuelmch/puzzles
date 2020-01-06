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

#pragma once

#include "common/arbitrary_container.h"

#include <array>
#include <cstdint>
#include <functional>

namespace Shurikens {

// Move and Cell should've been enums, but unfortunately this is more space-efficient
typedef uint8_t Move;
const Move swap_top = 0;
const Move turn_a = 1;
const Move turn_b = 2;

typedef uint8_t Cell;
const Cell A = 0;
const Cell B = 1;
const Cell C = 2;
const Cell D = 3;
const Cell E = 4;
const Cell F = 5;
const Cell G = 6;
const Cell H = 7;
const Cell I = 8;
const Cell J = 9;
const Cell K = 10;
const Cell L = 11;

const std::array<Move, 3> allMoves = {swap_top, turn_a, turn_b};
typedef Puzzles::ArbitraryContainer<allMoves.size()> MoveContainer;

class Shuriken {
public:
  explicit Shuriken(std::array<Cell, 12> cells) : cells(cells) {}

  Shuriken apply(Move move) const;

  inline bool isSolved() const { return *this == Shuriken({A, B, C, D, E, F, G, H, I, J, K, L}); }

  bool operator==(const Shuriken &other) const;

  const std::array<Cell, 12> cells;
};
}

namespace std {
template <> struct hash<Shurikens::Shuriken> {
  std::size_t operator()(const Shurikens::Shuriken &shuriken) const {
    auto first = 0;
    auto second = 0;

    for (int i = 0; i < 6; ++i) {
      first = (first * 31) + hash<int>()(shuriken.cells[i]);
      second = (second * 31) + hash<int>()(shuriken.cells[i + 6]);
    }

    return first * second;
  }
};
}
