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

#include "common/runners.h"
#include "travelling_salesman.h"
#include "travelling_salesman_data.h"

#include <iostream>

using Puzzles::runningTime;

bool ComSci::run() {
  auto [results, duration] = runningTime([] { return ComSci::TravellingSalesman::run(); });
  if (results.distance == KNOWN_SHORTEST_DISTANCE) {
    std::cout << "ComSci: Travelling Salesman found a correct path"
              << ", it took about " << duration << " µs!\n";
    return true;
  } else {
    std::cout << "ComSci: Travelling Salesman didn't find the shortest path, was expecting " << KNOWN_SHORTEST_DISTANCE
              << ", but got this: (";
    std::cout << results.distance << ")[";
    for (auto i : results.shortestPath) {
      std::cout << i << ", ";
    }
    std::cout << "]\n";
    return false;
  }
}
