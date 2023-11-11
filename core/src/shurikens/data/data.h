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

namespace Shurikens {

struct ShurikenData {

  ShurikenData(std::string name, Shuriken shuriken, const Shurikens::MoveContainer &solution)
    : name(std::move(name)), shuriken(std::move(shuriken)), solutions({solution}) {
  }

  ShurikenData(std::string name, Shuriken shuriken, const Shurikens::MoveContainer &solution0,
               const Shurikens::MoveContainer &solution1)
    : name(std::move(name)), shuriken(std::move(shuriken)), solutions({solution0, solution1}) {
    assert(solution0.size() == solution1.size());
  }

  inline size_t solutionSize() const { return solutions.cbegin()->size(); }

  inline bool isSolution(const Shurikens::MoveContainer &solution) const {
    if (solution.size() != solutions.cbegin()->size()) return false;

    const bool isExactSolution = solutions.find(solution) != solutions.end();
    if (isExactSolution) return true;

    const auto &lastMove = solution.at(solution.size() - 1);
    // If the last move is a swap, it doesn't matter if it's top or bottom
    if (lastMove == swap_top) {
      // TODO: This for loop should've been `MoveContainer copy{solution.cbegin(), solution.cend() - 1};` instead
      MoveContainer copy;
      for (size_t i = 0; i < solution.size() - 1; ++i) {
        copy.push(solution[i]);
      }
      copy.push(swap_bottom);
      return solutions.find(copy) != solutions.end();
    } else if (lastMove == swap_bottom) {
      MoveContainer copy;
      for (size_t i = 0; i < solution.size() - 1; ++i) {
        copy.push(solution[i]);
      }
      copy.push(swap_top);
      return solutions.find(copy) != solutions.end();
    }

    return false;
  }

  const std::string name;
  const Shuriken shuriken;
  const std::set<Shurikens::MoveContainer> solutions;
};

std::vector<ShurikenData> createTrivialShurikens();
std::vector<ShurikenData> createEasyShurikens();
std::vector<ShurikenData> createRealShurikens();

inline std::vector<ShurikenData> createAllShurikens() {
  std::vector<ShurikenData> data = createTrivialShurikens();

  std::vector<ShurikenData> easy = createEasyShurikens();
  std::move(easy.begin(), easy.end(), std::back_inserter(data));

  std::vector<ShurikenData> real = createRealShurikens();
  std::move(real.begin(), real.end(), std::back_inserter(data));

  return data;
}
}
