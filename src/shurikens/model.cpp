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

#include "model.h"

#include <cassert>

using namespace Shurikens;

using std::array;
using std::swap;

static inline array<Cell, 12> doSwapTop(array<Cell, 12> cells) {
  swap(cells[0], cells[6]);
  swap(cells[1], cells[7]);
  swap(cells[2], cells[8]);

  return cells;
}

static inline array<Cell, 12> doSwapBottom(array<Cell, 12> cells) {
  swap(cells[3], cells[9]);
  swap(cells[4], cells[10]);
  swap(cells[5], cells[11]);

  return cells;
}

static inline array<Cell, 12> doInvert(array<Cell, 12> cells) {
  swap(cells[0], cells[6]);
  swap(cells[1], cells[7]);
  swap(cells[2], cells[8]);
  swap(cells[3], cells[9]);
  swap(cells[4], cells[10]);
  swap(cells[5], cells[11]);

  return cells;
}

static inline array<Cell, 12> doTurnA(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = {};

  for (int i = 0; i < 6; ++i) {
    turned[(i + 1) % 6] = cells[i];
    turned[i + 6] = cells[i + 6];
  }

  return turned;
}

static inline array<Cell, 12> doTurnB(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = {};

  for (int i = 0; i < 6; ++i) {
    turned[i] = cells[i];
    turned[((i + 1) % 6) + 6] = cells[i + 6];
  }

  return turned;
}

static inline array<Cell, 12> doReverseA(const array<Cell, 12> &cells) {
  //TODO: Improve this method
  auto first = doTurnA(cells);
  auto second = doTurnA(first);
  auto third = doTurnA(second);
  auto fourth = doTurnA(third);
  return doTurnA(fourth);
}

static inline array<Cell, 12> doReverseB(const array<Cell, 12> &cells) {
  //TODO: Improve this method
  auto first = doTurnB(cells);
  auto second = doTurnB(first);
  auto third = doTurnB(second);
  auto fourth = doTurnB(third);
  return doTurnB(fourth);
}

Shuriken Shuriken::apply(Shurikens::Move move) const {
  switch (move) {
  case swap_top:
    return Shuriken(doSwapTop(this->cells));
  case swap_bottom:
    return Shuriken(doSwapBottom(this->cells));
  case turn_a:
    return Shuriken(doTurnA(this->cells));
  case turn_b:
    return Shuriken(doTurnB(this->cells));
  case reverse_a:
    return Shuriken(doReverseA(this->cells));
  case reverse_b:
    return Shuriken(doReverseB(this->cells));
  default:
    assert(!"Tried to apply an invalid move!");
    return *this;
  }
}

bool Shuriken::operator==(const Shuriken &other) const {
  // TODO There must be a better way of doing this check...
  if (cells == other.cells) return true;
  if (cells == doInvert(other.cells)) return true;

  return false;
}
