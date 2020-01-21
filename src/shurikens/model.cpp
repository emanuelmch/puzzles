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

static inline array<Cell, 12> doSwapTop(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = cells;

  auto cellsBegin = cells.begin();
  auto turnedBegin = turned.begin();
  std::copy(cellsBegin, cellsBegin + 3, turnedBegin + 6);
  std::copy(cellsBegin + 6, cellsBegin + 9, turnedBegin);

  return turned;
}

static inline array<Cell, 12> doSwapBottom(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = cells;

  auto cellsBegin = cells.begin();
  auto turnedBegin = turned.begin();
  std::copy(cellsBegin + 3, cellsBegin + 6, turnedBegin + 9);
  std::copy(cellsBegin + 9, cellsBegin + 12, turnedBegin + 3);

  return turned;
}

static inline array<Cell, 12> doInvert(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = {};

  auto cellsBegin = cells.begin();
  auto turnedBegin = turned.begin();
  std::copy(cellsBegin, cellsBegin + 6, turnedBegin + 6);
  std::copy(cellsBegin + 6, cellsBegin + 12, turnedBegin);

  return turned;
}

static inline array<Cell, 12> doTurnA(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = cells;

  auto cellsBegin = cells.begin();
  std::copy(cellsBegin, cellsBegin + 5, turned.begin() + 1);
  turned[0] = cells[5];

  return turned;
}

static inline array<Cell, 12> doTurnB(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = cells;

  auto cellsBegin = cells.begin();
  std::copy(cellsBegin + 6, cellsBegin + 11, turned.begin() + 7);
  turned[6] = cells[11];

  return turned;
}

static inline array<Cell, 12> doReverseA(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = cells;

  auto cellsBegin = cells.begin();
  std::copy(cellsBegin + 1, cellsBegin + 6, turned.begin());
  turned[5] = cells[0];

  return turned;
}

static inline array<Cell, 12> doReverseB(const array<Cell, 12> &cells) {
  array<Cell, 12> turned = cells;

  auto cellsBegin = cells.begin();
  std::copy(cellsBegin + 7, cellsBegin + 12, turned.begin() + 6);
  turned[11] = cells[6];

  return turned;
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
