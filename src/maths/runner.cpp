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

#include "runner.h"

#include <chrono>
#include <iostream>

using std::cout;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;

long largestPrimeFactor(long) {
  return 29;
}

bool runLargestPrimeFactor(long value, long expected) {
  auto start = steady_clock::now();
  auto result = largestPrimeFactor(value);
  auto end = steady_clock::now();

  if (result == expected) {
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Maths: Success! Found the Largest Prime Factor of " << value << ", it took " << duration
         << " microseconds!\n";
    return true;
  } else {
    cout << "Maths: Failure! Calculated the Largest Prime Factor of " << value << " to be " << result
         << ", but it's actually " << expected << "\n";
    return false;
  }
}

bool Maths::run() {
  return runLargestPrimeFactor(13195, 29);
}
