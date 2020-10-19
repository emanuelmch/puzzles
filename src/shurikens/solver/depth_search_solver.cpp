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

#include "depth_search_solver.h"

#include "common/numbers.h"

#include <stack>
#include <unordered_map>

using namespace Shurikens;

namespace {
struct Node {
  const Shuriken shuriken;
  const MoveContainer moves;

  explicit Node(Shuriken shuriken) : shuriken(std::move(shuriken)), moves() {}
  Node(Shuriken shuriken, const MoveContainer &moves) : shuriken(std::move(shuriken)), moves(moves) {}
};
}

MoveContainer DepthSearchSolver::solve(const Shuriken &shuriken, size_t knownUpperBound) const {
  auto maxNodes = static_cast<size_t>(std::pow(allMoves.size(), knownUpperBound) + 1);
  auto maxShurikens = static_cast<size_t>(std::ceil(Puzzles::Numbers::factorial(12) / 2));

  std::unordered_map<Shuriken, uint8_t> cache;
  cache.reserve(std::min(maxNodes, maxShurikens));
  cache[shuriken] = 0;

  std::stack<Node> nodes;
  nodes.emplace(shuriken);

  MoveContainer bestSolution(knownUpperBound + 1);

  do {
    auto next = nodes.top();
    nodes.pop();

    if (next.moves.size() >= bestSolution.size()) {
      continue;
    }

    if (next.shuriken.isSolved()) {
      bestSolution = next.moves;
      continue;
    }

    for (auto &move : allMoves) {
      auto newShuriken = next.shuriken.apply(move);
      auto it = cache.find(newShuriken);

      if (it == cache.end() || it->second > (next.moves.size() + 1)) {
        MoveContainer newMoves = next.moves + move;
        cache[newShuriken] = newMoves.size();

        nodes.emplace(newShuriken, newMoves);
      }
    }
  } while (!nodes.empty());

  return bestSolution;
}
