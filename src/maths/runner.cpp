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
  auto expectedSequence = {1u,    2u,    4u,     6u,     12u,    24u,    36u,    48u,    60u,
                           120u,  180u,  240u,   360u,   720u,   840u,   1260u,  1680u,  2520u,
                           5040u, 7560u, 10080u, 15120u, 20160u, 25200u, 27720u, 45360u, 50400u};
  auto actualSequence = Sequences::highlyCompositeNumbers();
  return runInfiniteSequence("Highly Composite Number", expectedSequence, actualSequence);
}

bool runEmirpsSequence() {
  auto expectedSequence = {13u,   17u,   31u,   37u,   71u,   73u,   79u,   97u,   107u,  113u,  149u,  157u,  167u,
                           179u,  199u,  311u,  337u,  347u,  359u,  389u,  701u,  709u,  733u,  739u,  743u,  751u,
                           761u,  769u,  907u,  937u,  941u,  953u,  967u,  971u,  983u,  991u,  1009u, 1021u, 1031u,
                           1033u, 1061u, 1069u, 1091u, 1097u, 1103u, 1109u, 1151u, 1153u, 1181u, 1193u};
  auto actualSequence = Sequences::emirps();
  return runInfiniteSequence("Emirps", expectedSequence, actualSequence);
}

bool runSteppingStonesPuzzle() {
  constexpr std::array<uintmax_t, 7> expectedResults{0, 1, 16, 28, 38, 49, 60};

  struct result_type {
    bool success;
    uintmax_t index = 0;
    uintmax_t actualValue = 0;
  };

  auto [result, duration] = runningTime([&expectedResults] {
    for (uintmax_t i = 1u; i < expectedResults.size(); ++i) {
      auto expected = expectedResults[i];
      auto actual = Maths::steppingStones(i);
      if (actual != expected) {
        return result_type{.success = false, .index = i, .actualValue = actual};
      }
    }

    return result_type{.success = true};
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
