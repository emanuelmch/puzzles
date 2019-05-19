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

#include <array>
#include <cassert>
#include <sys/types.h>

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

class Shuriken {
public:
  explicit Shuriken(std::array<Cell, 12> cells) : cells(cells) {}

  Shuriken apply(Move move) const {
    switch (move) {
    case turn_a:
      return doTurnA();
    case turn_b:
      return doTurnB();
    case swap_top:
      return doSwapTop();
    default:
      assert(!"Tried to apply an invalid move!");
      return *this;
    }
  }

  bool isSolved() const { return cells == std::array<Cell, 12>({A, B, C, D, E, F, G, H, I, J, K, L}); }

  bool operator==(const Shuriken &other) const { return cells == other.cells; }

  const std::array<Cell, 12> cells;

private:
  inline Shuriken doSwapTop() const {
    auto swapped = this->cells;

    std::swap(swapped[0], swapped[6]);
    std::swap(swapped[1], swapped[7]);
    std::swap(swapped[2], swapped[8]);

    return Shuriken(swapped);
  }

  inline Shuriken doTurnA() const {
    std::array<Cell, 12> turned = {};

    for (int i = 0; i < 6; ++i) {
      turned[(i + 1) % 6] = this->cells[i];
      turned[i + 6] = this->cells[i + 6];
    }

    return Shuriken(turned);
  }

  inline Shuriken doTurnB() const {
    std::array<Cell, 12> turned = {};

    for (int i = 0; i < 6; ++i) {
      turned[i] = this->cells[i];
      turned[((i + 1) % 6) + 6] = this->cells[i + 6];
    }

    return Shuriken(turned);
  }
};
}

namespace std {
template <> struct hash<Shurikens::Shuriken> {
  std::size_t operator()(const Shurikens::Shuriken &shuriken) const {
    auto result = 0;
    for (auto cell : shuriken.cells) {
      result = (result * 31) + hash<int>()(cell);
    }
    return result;
  }
};
}
