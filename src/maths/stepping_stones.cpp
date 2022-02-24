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

#include <algorithm> // std::count_if
#include <array>
#include <map>
#include <queue>
#include <set>

namespace {
using Point = std::pair<int8_t, int8_t>;

struct Node {
  std::map<Point, uint8_t> board;
  uintmax_t max;

  Node() : board{}, max{0u} { apply(std::make_pair(0, 0), 1); }

  bool operator<(const Node &o) const { return board < o.board; }

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
      return 0U;
    }
  }

  [[nodiscard]] uintmax_t sum(Point center) const {
    uintmax_t sum = 0U;

    for (auto j = -1; j <= 1; ++j) {
      for (auto i = -1; i <= 1; ++i) {
        if (i == 0 && j == 0) {
          continue;
        }

        Point newPoint{center.first + i, center.second + j};
        sum += getOrZero(newPoint);
      }
    }

    return sum;
  }

  void apply(Point point, uintmax_t height) {
    ensure(height == max + 1 || (height == 1 && max == 1));
    ensure(board.contains(point) == false);

    board.emplace(point, height);
    max = height;

    // Ensure we have "less than zero" points to help with caching
    if (point.first < 0 || point.second < 0) {
      auto distance = 0 - std::min(point.first, point.second);
      decltype(board) newBoard;

      for (const auto &oldElem : board) {
        Point newPoint = {oldElem.first.first + distance, oldElem.first.second + distance};
        ensure(newPoint.first >= 0);
        ensure(newPoint.second >= 0);
        uintmax_t newHeight = oldElem.second;
        newBoard.emplace(newPoint, newHeight);
      }

      board = newBoard;
    }
  }
};
}

uintmax_t Maths::steppingStones(uint8_t startingStones) {
  ensure(startingStones > 0);

  decltype(Node::max) highestNode = 1;

  std::set<Node> cache;

  std::queue<Node> nodes;
  nodes.emplace();

  // First create all possible boards with `startingStones` startingStones nodes.emplace();
  ensure(nodes.front().board.size() == 1 && nodes.front().max == 1);

  while (nodes.front().board.size() < startingStones) {
    auto next = nodes.front();
    nodes.pop();

    for (const auto &boardItem : next.board) {
      const auto initialRangeSearch = 4;
      auto stone = boardItem.first;

      for (auto j = -initialRangeSearch; j <= initialRangeSearch; ++j) {
        for (auto i = -initialRangeSearch; i <= initialRangeSearch; ++i) {
          if (i == 0 && j == 0) { continue; }

          Point newPoint{stone.first + i, stone.second + j};
          if (next.board.contains(newPoint)) { continue; }

          auto newNode = next;
          newNode.apply(newPoint, 1U);
          nodes.push(newNode);
        }
      }
    }
  }

  // Now go through these boards and climb them
  do {
    auto next = nodes.front();
    nodes.pop();

    // We should ALWAYS have exactly `startingStones` stones with height 1
    ensure(std::count_if(next.board.cbegin(), next.board.cend(), [](auto elem) { return elem.second == 1; }) ==
           startingStones);

    const auto nextStone = next.max + 1;
    for (const auto &move : next.allPossibleMoves()) {
      ensure(next.board.contains(move) == false);

      if (next.sum(move) == nextStone) {
        Node newNode = next;
        newNode.apply(move, nextStone);

        auto alreadyExisted = cache.insert(newNode).second == false;
        if (alreadyExisted) {
          continue;
        }

        nodes.push(newNode);

        if (nextStone > highestNode) {
          highestNode = nextStone;
        }
      }
    }
  } while (!nodes.empty());

  return highestNode;
}
