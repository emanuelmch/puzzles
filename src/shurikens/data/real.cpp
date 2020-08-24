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

#include "data.h"

using namespace Shurikens;

using std::vector;

inline ShurikenData createReal0() {
  Shuriken shuriken({C, A, B, D, E, F, G, H, I, J, K, L});
  Shurikens::MoveContainer solution0 = {turn_a,    swap_top, turn_b, reverse_a, swap_top,  turn_a,   swap_top,
                                        reverse_b, swap_top, turn_b, swap_top,  reverse_b, swap_top, reverse_a};
  Shurikens::MoveContainer solution1 = {reverse_a, swap_top, reverse_b, swap_top,  turn_b, swap_top, reverse_b,
                                        swap_top,  turn_a,   swap_top,  reverse_a, turn_b, swap_top, turn_a};
  return ShurikenData("real0", shuriken, solution0, solution1);
}

inline ShurikenData createReal1() {
  Shuriken shuriken({B, A, C, D, E, F, G, H, I, J, K, L});
  Shurikens::MoveContainer solution0 = {swap_top, turn_a, reverse_b, swap_top,  turn_a,   turn_a, swap_top,
                                        turn_a,   turn_a, swap_top,  turn_a,    swap_top, turn_a, turn_a,
                                        swap_top, turn_b, swap_top,  reverse_a, swap_top, turn_a, turn_a};
  Shurikens::MoveContainer solution1 = {reverse_b, reverse_a, swap_top,  reverse_b, reverse_b, swap_top,  reverse_a,
                                        swap_top,  reverse_b, reverse_b, swap_top,  reverse_a, reverse_a, swap_top,
                                        reverse_b, turn_a,    swap_top,  reverse_a, swap_top,  turn_b,    swap_top};
  return ShurikenData("real1", shuriken, solution0, solution1);
}

vector<ShurikenData> Shurikens::createRealShurikens() {
  return {createReal0(), createReal1()};
}
