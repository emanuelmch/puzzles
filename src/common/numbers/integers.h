/*
 * Copyright (c) 2020 Emanuel Machado da Silva
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

#include "common/assertions.h"
#include "common/numbers/integer.h"

namespace pzl {

inline Integer greatestCommonDivisor(Integer left, Integer right) {
  // This is the Euclidean algorithm
  if (left == 0) return right;

  left = left.absolute();
  right = right.absolute();

  while (true) {
    if (right == 0) return left;
    left %= right;
    if (left == 0) return right;
    right %= left;
  }
}

inline Integer lowestCommonMultiple(const Integer &lhs, const Integer &rhs) {
  ensure(lhs != 0 && rhs != 0); // This is undefined
  auto gcd = greatestCommonDivisor(lhs, rhs);
  return lhs * rhs / gcd;
}
}
