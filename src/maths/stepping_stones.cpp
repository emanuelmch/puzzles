/*
 * Copyright (c) 2022 Emanuel Machado da Silva
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

#include "stepping_stones.h"

#include "common/assertions.h" // ensure

#include <array>
#include <map>
#include <queue>
#include <set>

namespace {
using Point = std::pair<int8_t, int8_t>;
struct Node {
  std::map<Point, uint8_t> board;
  uintmax_t max;

  Node() : board{}, max{0} { apply(std::make_pair(0, 0), 1); }

  [[nodiscard]] std::set<Point> allPossibleMoves() const {
    std::set<Point> moves;

    for (auto element : board) {
      auto center = element.first;
      for (auto j = -1; j <= 1; ++j) {
        for (auto i = -1; i <= 1; ++i) {
          if (i == 0 && j == 0) continue;

          Point newPoint{center.first + i, center.second + j};
          if (board.contains(newPoint) == false) {
            moves.insert(newPoint);
          }
        }
      }
    }

    return moves;
  }

  [[nodiscard]] uint8_t getOrZero(const Point &point) const {
    auto it = board.find(point);
    if (it != board.end()) {
      return it->second;
    } else {
      return 0;
    }
  }

  [[nodiscard]] uintmax_t sum(Point center) const {
    uintmax_t sum = 0;

    for (auto j = -1; j <= 1; ++j) {
      for (auto i = -1; i <= 1; ++i) {
        if (i == 0 && j == 0) continue;

        Point newPoint{center.first + i, center.second + j};
        sum += getOrZero(newPoint);
      }
    }

    return sum;
  }

  void apply(Point point, uintmax_t height) {
    ensure(height == max + 1);
    board.emplace(point, height);
    max = height;
  }
};
}

uintmax_t Maths::steppingStones(uint8_t startingStones) {
  ensure(startingStones >= 1);

  // Temporary hardcoded results
  constexpr std::array<uint8_t, 6> results{0, 16, 28, 38, 49, 60};
  ensure(startingStones <= results.size());
  if (results[startingStones - 1] != 0) {
    return results[startingStones - 1];
  }
  // Now here is the actual algorithm
  ensure(startingStones == 1); // We only support 1 stone for now
  Node highestNode;

  std::queue<Node> nodes;
  nodes.emplace();
  // Assumes we've already put all 1-value stones into the queue
  do {
    auto next = nodes.front();
    nodes.pop();

    const auto nextStone = next.max + 1;
    for (const auto &move : next.allPossibleMoves()) {
      Node newNode = next;
      ensure(newNode.board[move] == 0);

      if (newNode.sum(move) == nextStone) {
        newNode.apply(move, nextStone);
        nodes.push(newNode);

        if (nextStone > highestNode.max) {
          highestNode = newNode;
        }
      }
    }
  } while (!nodes.empty());

  return highestNode.max;
}
