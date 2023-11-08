/*
 * Copyright (c) 2021 Emanuel Machado da Silva
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

#include "common/ranges.h"
#include "common/runners.h"
#include "common/strings.h"
#include "constrained_ordering.h"
#include "travelling_salesman.h"
#include "travelling_salesman_data.h"

#include <array>
#include <iostream>

using Puzzles::runningTime;

bool runConstrainedOrdering() {
  const std::vector<std::string> cows = {"Bessie", "Buttercup", "Belinda", "Beatrice", "Bella", "Blue", "Betsy", "Sue"};
  const std::vector<std::string> constraints = {
      "Buttercup must be milked beside Bella",
      "Blue must be milked beside Bella",
      "Sue must be milked beside Beatrice"
  };

  auto solvers = {
      std::make_pair("Baseline", &ComSci::ConstrainedOrdering::runBaseline),
      std::make_pair("Heuristic", &ComSci::ConstrainedOrdering::runHeuristic)
  };

  for (const auto &solver: solvers) {
    const auto name = solver.first;
    const auto function = solver.second;
    auto [results, duration] = runningTime([&] { return function(cows, constraints); });

    const std::array<std::vector<std::string>, 2> possibleSolutions = {
        std::vector<std::string>{
            "Beatrice",
            "Sue",
            "Belinda",
            "Bessie",
            "Betsy",
            "Blue",
            "Bella",
            "Buttercup"
        },
        std::vector<std::string>{
            "Blue",
            "Bella",
            "Buttercup",
            "Beatrice",
            "Sue",
            "Bessie",
            "Belinda",
            "Betsy"
        }
    };
    if (pzl::ranges::contains(possibleSolutions, results)) {
      std::cout << "Constrained Ordering: " << name << " found a known valid order"
                << ", it took about " << duration << " µs!\n";
    } else {
      std::cout << "Constrained Ordering: " << name << " didn't find a known valid order. Received this:\n"
                << "[" << Puzzles::join(results.cows, ", ") << "]\n";
      return false;
    }
  }

  return true;
}

bool runTravellingSalesman() {
  auto [results, duration] = runningTime([] { return ComSci::TravellingSalesman::run(); });
  if (results.distance == KNOWN_SHORTEST_DISTANCE) {
    std::cout << "ComSci: Travelling Salesman found a correct path"
              << ", it took about " << duration << " µs!\n";
    return true;
  } else {
    std::cout << "ComSci: Travelling Salesman didn't find the shortest path, was expecting "
              << KNOWN_SHORTEST_DISTANCE
              << ", but got this: (";
    std::cout << results.distance << ")[";
    for (auto i: results.shortestPath) {
      std::cout << i << ", ";
    }
    std::cout << "]\n";
    return false;
  }
}

bool ComSci::run() {
  return runConstrainedOrdering() && runTravellingSalesman();
}
