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

#include "common/arbitrary_container.h"

#include <stack>
#include <sys/types.h>
#include <unordered_map>
#include <utility>

using namespace Shurikens;

using std::move;
using std::stack;
using std::unordered_map;
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

vector<Move> DepthSearchSolver::solve(const Shuriken &shuriken, size_t knownUpperBound) const {
  unordered_map<Shuriken, u_int8_t> cache;
  cache[shuriken] = 0;

  stack<Node> nodes;
  nodes.emplace(shuriken);

  // TODO Find a better way of starting with knownUpperBound items
  MoveStorage bestSolution;
  for (size_t i = 0; i <= knownUpperBound; ++i) {
    bestSolution.push(0);
  }

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
        MoveStorage newMoves(next.moves);
        newMoves.push(move);
        cache[newShuriken] = newMoves.size();

        nodes.emplace(newShuriken, newMoves);
      }
    }
  } while (nodes.empty() == false);

  return static_cast<vector<Move>>(bestSolution);
}