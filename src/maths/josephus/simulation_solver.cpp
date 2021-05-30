/*
 * Copyright (c) 2021 Emanuel Machado da Silva
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

#include "solver.h"

#include "common/assertions.h"
#include "common/memory.h"

#include <utility>

using namespace Maths::Josephus;
using pzl::Integer;

namespace {
struct CircleItem {
  const Integer value;
  pzl::shared_ptr<CircleItem> next;

  explicit CircleItem(Integer value) : value{std::move(value)}, next{nullptr} {}
};
}

inline pzl::shared_ptr<CircleItem> makeCircle(const Integer &size) {
  auto first = pzl::make_shared<CircleItem>(Integer{1});

  auto circle = first;
  for (auto i = Integer{2}; i <= size; ++i) {
    circle->next = pzl::make_shared<CircleItem>(i);
    circle = circle->next;
  }

  ensure(!circle->next);
  circle->next = first;

  return first;
}

Integer SimulationSolver::solve(const Integer &initialSize) {
  ensure(initialSize > 0);

  auto item = makeCircle(initialSize);
  ensure(item->value == 1);

  while (item->next != item) {
    item->next = item->next->next;
    item = item->next;
  }

  item->next.reset(); // To avoid a cyclical reference

  return item->value;
}
