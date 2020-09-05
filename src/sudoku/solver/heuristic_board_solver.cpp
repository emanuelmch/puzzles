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

#include "heuristic_board_solver.h"

#include <cstdint>
#include <vector>

using namespace Sudoku;

using std::vector;

const int SIZE = 9;
const int CELL_COUNT = SIZE * SIZE;

const vector<vector<bool>> findCandidates(const Board &board);
void removeCandidatesFromColumn(int index, uint8_t value, vector<vector<bool>> *candidates);
void removeCandidatesFromRow(int index, uint8_t value, vector<vector<bool>> *candidates);
void removeCandidatesFromSquare(int index, uint8_t value, vector<vector<bool>> *candidates);
bool applyCandidates(Board *board, const vector<vector<bool>> &candidates);
uint8_t getSingleCandidate(const vector<bool> &candidates);

const Board HeuristicBoardSolver::solve(const Sudoku::Board &original) const {
  auto board = original;
  bool changedAny;
  do {
    auto candidates = findCandidates(board);
    changedAny = applyCandidates(&board, candidates);
  } while (changedAny);
  return board;
}

const vector<vector<bool>> findCandidates(const Board &board) {
  vector<vector<bool>> candidates;

  candidates.reserve(CELL_COUNT);
  for (auto i = 0; i < CELL_COUNT; ++i) {
    candidates.push_back({true, true, true, true, true, true, true, true, true});
  }

  for (int i = 0; i < CELL_COUNT; ++i) {
    auto cell = board.getCell(i);
    if (cell != 0) {
      removeCandidatesFromColumn(i, cell, &candidates);
      removeCandidatesFromRow(i, cell, &candidates);
      removeCandidatesFromSquare(i, cell, &candidates);
    }
  }

  return candidates;
}

void removeCandidatesFromColumn(int index, uint8_t value, vector<vector<bool>> *candidates) {
  auto upwards = index - SIZE;
  while (upwards >= 0) {
    (*candidates)[upwards][value - 1] = false;
    upwards -= SIZE;
  }

  auto downwards = index + SIZE;
  while (downwards < CELL_COUNT) {
    (*candidates)[downwards][value - 1] = false;
    downwards += SIZE;
  }
}

void removeCandidatesFromRow(int index, uint8_t value, vector<vector<bool>> *candidates) {
  auto rem = index % SIZE;
  for (auto i = 1; i <= rem; ++i) {
    (*candidates)[index - i][value - 1] = false;
  }

  for (auto i = 1; i < (SIZE - rem); ++i) {
    (*candidates)[index + i][value - 1] = false;
  }
}

void removeCandidatesFromSquare(int index, uint8_t value, vector<vector<bool>> *candidates) {
  uint8_t rows[3] = {
      0,
  };
  switch ((index / 9) % 3) {
  case 0:
    rows[0] = (index / 9);
    rows[1] = (index / 9) + 1;
    rows[2] = (index / 9) + 2;
    break;
  case 1:
    rows[0] = (index / 9) - 1;
    rows[1] = (index / 9);
    rows[2] = (index / 9) + 1;
    break;
  case 2:
    rows[0] = (index / 9) - 2;
    rows[1] = (index / 9) - 1;
    rows[2] = (index / 9);
  }

  uint8_t columns[3] = {
      0,
  };
  switch (index % SIZE % 3) {
  case 0:
    columns[0] = index % SIZE;
    columns[1] = index % SIZE + 1;
    columns[2] = index % SIZE + 2;
    break;
  case 1:
    columns[0] = index % SIZE - 1;
    columns[1] = index % SIZE;
    columns[2] = index % SIZE + 1;
    break;
  case 2:
    columns[0] = index % SIZE - 2;
    columns[1] = index % SIZE - 1;
    columns[2] = index % SIZE;
  }

  for (auto row : rows) {
    for (auto column : columns) {
      (*candidates)[row * SIZE + column][value - 1] = false;
    }
  }
}

bool applyCandidates(Board *board, const vector<vector<bool>> &candidates) {
  auto changedAny = false;

  for (int i = 0; i < CELL_COUNT; ++i) {
    if (board->getCell(i) == 0) {
      auto cands = candidates[i];
      auto value = getSingleCandidate(cands);
      if (value != 0) {
        board->setCell(i, value);
        changedAny = true;
      }
    }
  }

  return changedAny;
}

uint8_t getSingleCandidate(const vector<bool> &candidates) {
  auto value = 0;

  for (auto i = 0; i < SIZE; ++i) {
    if (candidates[i]) {
      if (value == 0) {
        value = i + 1;
      } else {
        return 0;
      }
    }
  }

  return value;
}
