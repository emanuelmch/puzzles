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

#include "brute_force_board_solver.h"

#include <cassert>
#include <stack>
#include <vector>

using namespace CPic;

using std::stack;
using std::vector;

namespace {
struct Node {
public:
  explicit Node(const Board *_board, const BoardState &_state) : board(_board), state(_state), nextRow(0), nextCol(0) {}

  Node(const Node &other) = default;

  ~Node() = default;

  const vector<Node> getNext() const {
    auto lastCell = board->rowCount * board->columnCount;
    vector<Node> next;
    auto nextCell = (nextRow * board->columnCount) + nextCol;
    if (nextCell == lastCell || !state.isValid(board)) return next;

    for (auto color : board->colors) {
      Node other(*this);
      other.state.setColorAt(nextCol, nextRow, color);
      other.nextCol++;

      if (other.nextCol == this->board->columnCount) {
        other.nextCol = 0;
        other.nextRow++;
      }

      next.push_back(other);
    }

    return next;
  }

  bool isSolution() const {
    auto nextCell = (nextRow * board->columnCount) + nextCol;
    auto lastCell = board->rowCount * board->columnCount;
    return nextCell == lastCell && state.isValid(board);
  }

  const Board *board;
  BoardState state;

private:
  ushort nextRow, nextCol;
};
}

BoardState BruteForceBoardSolver::solve(const Board *board) const {
  assert(board->columnCount > 0);
  assert(board->rowCount > 0);

  stack<Node> nodes;
  const auto emptyState = BoardState(board->columnCount, board->rowCount);

  nodes.push(Node(board, emptyState));

  do {
    auto top = nodes.top();
    if (top.isSolution()) {
      return top.state;
    } else {
      nodes.pop();
      for (const auto &node : top.getNext()) {
        nodes.push(node);
      }
    }
  } while (!nodes.empty());

  // Couldn't find anything!
  return emptyState;
}
