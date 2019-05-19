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

#pragma once

#include "shurikens/model.h"

#include <cassert>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace Shurikens {

struct ShurikenData {

  ShurikenData(std::string name, Shuriken shuriken, const std::vector<Move> &solution)
      : name(std::move(name)), shuriken(std::move(shuriken)), solutions({solution}) {}

  ShurikenData(std::string name, Shuriken shuriken, const std::vector<Move> &solution0,
               const std::vector<Move> &solution1)
      : name(std::move(name)), shuriken(std::move(shuriken)), solutions({solution0, solution1}) {
    assert(solution0.size() == solution1.size());
  }

  inline size_t solutionSize() const { return solutions.cbegin()->size(); }
  inline bool isSolution(const std::vector<Move> &solution) const {
    return solutions.find(solution) != solutions.end();
  }

  const std::string name;
  const Shuriken shuriken;
  const std::set<std::vector<Move>> solutions;
};

std::vector<ShurikenData> createTrivialShurikens();
std::vector<ShurikenData> createRealShurikens();

inline std::vector<ShurikenData> createAllShurikens() {
  std::vector<ShurikenData> data = createTrivialShurikens();

  std::vector<ShurikenData> real = createRealShurikens();
  std::move(real.begin(), real.end(), std::back_inserter(data));

  return data;
}
}
