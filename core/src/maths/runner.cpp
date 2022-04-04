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
#include "josephus/solver.h"
#include "primes.h"
#include "sequences.h"
#include "stepping_stones.h"

#include "common/runners.h"
#include "common/views.h"

#include <array> // std::array
#include <iostream>
#include <string>

#if __has_include(<version>)
#include <version>
#endif

using namespace Maths;

using Puzzles::LazySequence;
using Puzzles::runningTime;

using std::cout;
using std::string;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;

bool runLargestPrimeFactor(uintmax_t value, uintmax_t expected) {
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

bool runJosephusProblem(const intmax_t circleSize, const intmax_t expected) {
  pzl::Integer circle{circleSize};
  auto [arithmeticResult, arithmeticDuration] =
      runningTime([&circle] { return Maths::Josephus::ArithmeticSolver::solve(circle); });
  if (arithmeticResult != expected) {
    cout << "Maths: Failure! Arithmetic calculated a Josephus Circle of size " << circleSize
         << " to have a survivor on position " << std::to_string(arithmeticResult);
    return false;
  }
  auto [simulationResult, simulationDuration] =
      runningTime([&circle] { return Maths::Josephus::SimulationSolver::solve(circle); });
  if (simulationResult != expected) {
    cout << "Maths: Failure! Simulation calculated a Josephus Circle of size " << circleSize
         << " to have a survivor on position " << std::to_string(simulationResult);
    return false;
  }

  cout << "Maths: Success! Both Josephus solvers had the same correct result, arithmetic took " << arithmeticDuration
       << " µs, and simulation took " << simulationDuration << " µs\n";
  return true;
}

#if !defined(__cpp_impl_coroutine)
template <typename list>
bool runInfiniteSequence(const string &name, const list &, const Puzzles::LazySequence<uintmax_t> &) {
  cout << "Maths: Skipping " << name << " due to lack of compiler support\n";
  return true;
}
#else  // !defined(__cpp_impl_coroutine)
template <typename list>
bool runInfiniteSequence(const string &name, const list &expectedSequence,
                         const Puzzles::LazySequence<uintmax_t> &actualSequence) {
  struct result_type {
    bool success = true;
    size_t count = 0;
    size_t error = 0;
  };

  auto [result, duration] = runningTime([&expectedSequence, &actualSequence] {
    result_type result;

    for (auto [actual, expected] :
         Puzzles::zip(actualSequence.begin(), actualSequence.end(), expectedSequence.begin(), expectedSequence.end())) {
      if (actual == expected) {
        result.count++;
      } else {
        result.success = false;
        result.error = actual;
        break;
      }
    }

    return result;
  });

  if (result.success) {
    ensure_m(expectedSequence.size() == result.count,
             "Expected " << expectedSequence.size() << " numbers, got " << result.count);
    cout << "Maths: Success! Calculated " << expectedSequence.size() << " integers of the " << name
         << " sequence, it took " << duration << " microseconds!\n";
  } else {
    auto iterator = expectedSequence.begin();
    std::advance(iterator, result.count);
    cout << "Maths: Failure! The next " << name << " returned was " << result.error << ", but it should've been "
         << *iterator << "\n";
  }

  return result.success;
}
#endif // !defined(__cpp_impl_coroutine)

bool runHighlyCompositeNumberSequence() {
  auto expectedSequence = {1U,    2U,    4U,     6U,     12U,    24U,    36U,    48U,    60U,
                           120U,  180U,  240U,   360U,   720U,   840U,   1260U,  1680U,  2520U,
                           5040U, 7560U, 10080U, 15120U, 20160U, 25200U, 27720U, 45360U, 50400U};
  auto actualSequence = Sequences::highlyCompositeNumbers();
  return runInfiniteSequence("Highly Composite Number", expectedSequence, actualSequence);
}

bool runEmirpsSequence() {
  auto expectedSequence = {13U,   17U,   31U,   37U,   71U,   73U,   79U,   97U,   107U,  113U,  149U,  157U,  167U,
                           179U,  199U,  311U,  337U,  347U,  359U,  389U,  701U,  709U,  733U,  739U,  743U,  751U,
                           761U,  769U,  907U,  937U,  941U,  953U,  967U,  971U,  983U,  991U,  1009U, 1021U, 1031U,
                           1033U, 1061U, 1069U, 1091U, 1097U, 1103U, 1109U, 1151U, 1153U, 1181U, 1193U};
  auto actualSequence = Sequences::emirps();
  return runInfiniteSequence("Emirps", expectedSequence, actualSequence);
}

bool runSteppingStonesPuzzle() {
  constexpr std::array<uintmax_t, 3> expectedResults{0, 1, 16};

  struct resultType {
    bool success;
    uintmax_t index = 0;
    uintmax_t actualValue = 0;
  };

  auto [result, duration] = runningTime([&expectedResults] {
    for (uintmax_t i = 1U; i < expectedResults.size(); ++i) {
      auto expected = expectedResults[i];
      auto actual = Maths::steppingStones(i);
      if (actual != expected) {
        return resultType{.success = false, .index = i, .actualValue = actual};
      }
    }

    return resultType{.success = true};
  });

  if (result.success) {
    cout << "Maths: Success! Calculated the maximum \"height\" one can achieve with up to "
         << expectedResults.size() - 1 << " stones, it took " << duration << " microseconds!\n";
  } else {
    cout << "Maths: Failure! Calculated the maximum \"height\" one can achieve with " << result.index
         << " stones to be " << result.actualValue << ", but it should've been " << expectedResults[result.index]
         << "\n";
  }

  return result.success;
}

bool Maths::run() {
  return runLargestPrimeFactor(13195, 29) && runEvaluateExpression("3 + (4 * 2) ^ 2 ^ 3 / ( 1 - 5 ) ^ 2", 1048579) &&
         runJosephusProblem(139562, 16981) && runHighlyCompositeNumberSequence() && runEmirpsSequence() &&
         runSteppingStonesPuzzle();
}
