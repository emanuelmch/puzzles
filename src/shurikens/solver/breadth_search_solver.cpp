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

#include "breadth_search_solver.h"

#include "common/arbitrary_container.h"
#include "common/numbers.h"

#include <cmath>
#include <queue>
#include <unordered_set>
#include <utility>

using namespace Puzzles;
using namespace Shurikens;

using std::move;
using std::queue;
using std::unordered_set;
using std::vector;

typedef Puzzles::ArbitraryContainer<allMoves.size()> MoveStorage;

namespace {
struct Node {
  const Shuriken shuriken;
  const MoveStorage moves;

  explicit Node(Shuriken shuriken) : shuriken(move(shuriken)), moves() {}
  Node(Shuriken shuriken, MoveStorage moves) : shuriken(move(shuriken)), moves(move(moves)) {}
};
}

vector<Move> BreadthSearchSolver::solve(const Shuriken &shuriken, size_t knownUpperBound) const {
  auto maxNodes = static_cast<size_t>(std::pow(allMoves.size(), knownUpperBound) + 1);
  auto maxShurikens = static_cast<size_t>(std::ceil(Numbers::factorial(12) / 2));

  unordered_set<Shuriken> cache;
  cache.reserve(std::min(maxNodes, maxShurikens));
  cache.insert(shuriken);

  queue<Node> nodes;
  nodes.emplace(shuriken);

  do {
    auto next = nodes.front();
    if (next.shuriken.isSolved()) {
      return static_cast<vector<Move>>(next.moves);
    }

    nodes.pop();

    for (auto &move : allMoves) {
      auto newShuriken = next.shuriken.apply(move);
      if (cache.insert(newShuriken).second) {
        MoveStorage newMoves(next.moves);
        newMoves.push(move);

        nodes.emplace(newShuriken, newMoves);
      }
    }
  } while (!nodes.empty());

  return {};
}
