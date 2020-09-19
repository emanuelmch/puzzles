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

#include "expressions.h"
#include "primes.h"

#include "common/runners.h"

#include <chrono>
#include <iostream>
#include <string>

using namespace Maths;

using Puzzles::runningTime;

using std::cout;
using std::string;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;

bool runLargestPrimeFactor(long value, long expected) {
  auto [result, duration] = runningTime([value] { return largestPrimeFactor(value); });

  if (result == expected) {
    cout << "Maths: Success! Found the Largest Prime Factor of " << value << ", it took " << duration
         << " microseconds!\n";
    return true;
  } else {
    cout << "Maths: Failure! Calculated the Largest Prime Factor of " << value << " to be " << result
         << ", but it's actually " << expected << "\n";
    return false;
  }
}

bool runEvaluateExpression(const string &expression, long expected) {
  auto [result, duration] = runningTime([&expression] { return evaluateExpression(expression); });

  if (result == expected) {
    cout << "Maths: Success! Found the result of " << expression << ", it took " << duration << " microseconds!\n";
    return true;
  } else {
    cout << "Maths: Failure! Calculated the result of " << expression << " to be " << result << ", but it's actually "
         << expected << "\n";
    return false;
  }
}

bool Maths::run() {
  return runLargestPrimeFactor(13195, 29) && runEvaluateExpression("3 + (4 * 2) ^ 2 ^ 3 / ( 1 - 5 ) ^ 2", 1048579);
}
