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

#include <queue>
#include <vector>

using namespace CPic;

using std::queue;
using std::vector;

typedef unsigned short ushort;

struct Node {
public:
  Node(Board board) : board(board), nextRow(0), nextCol(0) {
    for (ushort row = 0; row < board.rowCount; ++row) {
      for (ushort col = 0; col < board.columnCount; ++col) {
        this->board.results[col][row] = C0;
      }
    }
  }

  Node(const Node &other) :
          board(other.board),
          nextRow(other.nextRow),
          nextCol(other.nextCol) {}

  ~Node() {}

  const vector<Node> getNext() const {
    vector<Node> next;
    if (nextRow == this->board.rowCount) return next;

    for (auto color: board.colors) {
      Node other(*this);
      other.board.results[nextRow][nextCol] = color;
      other.nextCol++;

      if (other.nextCol == this->board.columnCount) {
        other.nextCol = 0;
        other.nextRow++;
      }

      next.push_back(other);
    }

    return next;
  }

  Board board;

private:
  ushort nextRow, nextCol;
};

void BruteForceBoardSolver::solve(Board *board) const {
  queue<Node> nodes;
  nodes.push(Node(*board));

  while (!nodes.empty()) {
    auto front = nodes.front();
    if (front.board.isValid()) {
      board->results = front.board.results;
      return;
    } else {
      nodes.pop();
      auto next = front.getNext();
      for (ushort i = 0; i < next.size(); ++i) {
        nodes.push(next[i]);
      }
    }
  }
}
