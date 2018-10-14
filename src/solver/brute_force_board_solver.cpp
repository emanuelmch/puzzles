/*
 * Copyright (c) 2018 Emanuel Machado da Silva
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
#include <queue>
#include <utility>
#include <vector>

using namespace CPic;

using std::queue;
using std::vector;

typedef unsigned short ushort;

struct Node {
public:
  explicit Node(const Board *_board, BoardState _state) :
          board(_board), state(std::move(_state)), nextRow(0), nextCol(0) {}

  Node(const Node &other) = default;

  ~Node() = default;

  const vector<Node> getNext() const {
    vector<Node> next;
    if (nextRow == this->board->rowCount) return next;

    for (auto color: board->colors) {
      Node other(*this);
      other.state.setColorAt(nextRow, nextCol, color);
      other.nextCol++;

      if (other.nextCol == this->board->columnCount) {
        other.nextCol = 0;
        other.nextRow++;
      }

      next.push_back(other);
    }

    return next;
  }

  const Board *board;
  BoardState state;

private:
  ushort nextRow, nextCol;
};

BoardState BruteForceBoardSolver::solve(const Board *board) const {
  assert(board->columnCount > 0);
  assert(board->rowCount > 0);
  queue<Node> nodes;
  vector<BoardColumn> emptyBoard(board->columnCount, BoardColumn(vector<Color>(board->rowCount, C0)));
  nodes.push(Node(board, BoardState(emptyBoard)));

  const Node *lastNode = nullptr;
  while (!nodes.empty()) {
    auto front = nodes.front();
    if (front.state.isValid(front.board)) {
      return front.state;
    } else {
      nodes.pop();
      auto next = front.getNext();
      for (const auto &node : next) {
        nodes.push(node);
        lastNode = &node;
      }
    }
  }

  assert(lastNode != nullptr);

  return lastNode->state;
}
