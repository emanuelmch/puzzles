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

#include "threaded_search_solver.h"

#include "common/numbers.h"

#include <cstdint>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace Shurikens;
using namespace std::chrono_literals;

namespace {
const auto WORKER_COUNT = std::min(static_cast<size_t>(std::thread::hardware_concurrency()), allMoves.size());

struct Node {
  Shuriken shuriken;
  MoveContainer moves;

  Node(const Shuriken &shuriken, MoveContainer moves) : shuriken(shuriken), moves(std::move(moves)) {}
};

struct WorkerState {

  WorkerState(const Shuriken &shuriken, size_t knownUpperBound) : solution(knownUpperBound + 1) {
    for (auto &move : allMoves) {
      auto newShuriken = shuriken.apply(move);

      if (newShuriken.isSolved()) {
        solution = MoveContainer{move};
        break;
      }

      nodes.emplace(newShuriken, MoveContainer{move});
    }
  }

  inline void addNodes(const std::vector<Node> &newNodes, size_t depth) {
    if (!newNodes.empty() && depth + 1 < getSolutionSize()) {
      std::unique_lock lock(nodesMutex);
      for (const auto &node : newNodes) {
        nodes.push(node);
      }
    }
  }

  std::optional<Node> next() {
    std::unique_lock lock(nodesMutex);
    if (nodes.empty()) {
      return std::nullopt;
    }

    auto max = getSolutionSize();

    auto next = nodes.front();
    nodes.pop();

    assert(next.shuriken.isSolved() == false);
    while (next.moves.size() + 1 >= max && !nodes.empty()) {
      next = nodes.front();
      nodes.pop();
      assert(next.shuriken.isSolved() == false);
    }
    lock.unlock();

    if (next.moves.size() + 1 >= max) [[unlikely]] {
      return std::nullopt;
    }

    return std::optional{next};
  }

  inline MoveContainer getSolution() { return solution; }
  inline size_t getSolutionSize() { return solution.size(); }

  inline void setSolution(const MoveContainer &newSolution) {
    auto newSolutionSize = newSolution.size();
    if (newSolutionSize < solution.size()) {
      std::unique_lock lock(solutionMutex);

      if (newSolutionSize < solution.size()) {
        this->solution = newSolution;
      }
    }
  }

private:
  std::mutex nodesMutex, solutionMutex;

  std::queue<Node> nodes;
  MoveContainer solution;
};
}

inline bool addToCache(std::unordered_map<Shuriken, uint8_t> *cache, const Shuriken &shuriken, uint8_t depth) {
  auto it = cache->find(shuriken);

  if (it == cache->end()) [[likely]] {
    cache->insert({shuriken, depth});
    return true;
  }

  if (it->second > depth) [[unlikely]] {
    it->second = depth;
    return true;
  }

  return false;
}

static void workerFunction(WorkerState *state, size_t maxCacheSize) {
  std::unordered_map<Shuriken, uint8_t> cache;
  cache.reserve(maxCacheSize / 2);

  for (auto next = state->next(); next; next = state->next()) {
    std::vector<Node> newNodes;
    auto newShurikenDepth = next->moves.size() + 1;

    for (auto &move : allMoves) {
      auto newShuriken = next->shuriken.apply(move);
      if (newShuriken.isSolved()) {
        state->setSolution(next->moves + move);
        break;
      }

      if (addToCache(&cache, newShuriken, newShurikenDepth)) {
        newNodes.emplace_back(newShuriken, next->moves + move);
      }
    }
    state->addNodes(newNodes, newShurikenDepth);
  }
}

MoveContainer ThreadedSearchSolver::solve(const Shuriken &shuriken, size_t knownUpperBound) const {
  if (shuriken.isSolved()) return {};

  WorkerState state(shuriken, knownUpperBound);
  constexpr size_t maxShurikens = Puzzles::Numbers::factorial(12) / 2;
  size_t maxNodes = std::pow(allMoves.size(), knownUpperBound);
  auto maxCacheSize = std::min(maxShurikens, maxNodes);

  std::vector<std::thread> workers;
  workers.reserve(WORKER_COUNT);
  for (auto i = 0u; i < WORKER_COUNT; ++i) {
    workers.emplace_back(workerFunction, &state, maxCacheSize);
  }

  for (auto &worker : workers) {
    worker.join();
  }

  return state.getSolution();
}
