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

#include <queue>
#include <unordered_set>
#include <utility>

using namespace Shurikens;

using std::move;
using std::queue;
using std::unordered_set;
using std::vector;

namespace {
struct Node {
  const Shuriken shuriken;
  const vector<Move> moves;

  explicit Node(Shuriken shuriken) : shuriken(move(shuriken)), moves() {}
  Node(Shuriken shuriken, vector<Move> moves) : shuriken(move(shuriken)), moves(move(moves)) {}
};
}

vector<Move> BreadthSearchSolver::solve(const Shuriken &shuriken) const {
  unordered_set<Shuriken> cache;
  cache.insert(shuriken);

  queue<Node> nodes;
  nodes.emplace(shuriken);

  do {
    auto next = nodes.front();
    if (next.shuriken.isSolved()) {
      return next.moves;
    }

    nodes.pop();

    for (auto &move : allMoves) {
      auto newShuriken = next.shuriken.apply(move);
      if (cache.insert(newShuriken).second) {
        vector<Move> newMoves(next.moves);
        newMoves.push_back(move);
        newMoves.shrink_to_fit();

        nodes.emplace(newShuriken, newMoves);
      }
    }
  } while (!nodes.empty());

  return {};
}
