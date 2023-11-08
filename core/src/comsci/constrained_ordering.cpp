/*
 * Copyright (c) 2023 Emanuel Machado da Silva
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

#include "constrained_ordering.h"

#include <algorithm>
#include <cmath>
#include <deque>
#include <map>

/*
 * USACO 2019 December context, Bronze
 * Problem 3. Livestock Lineup
 *
 * Every day, Farmer John milks his 8 dairy cows, named
 * Bessie, Buttercup, Belinda, Beatrice, Bella, Blue, Betsy, and Sue.
 *
 * The cows are rather picky, unfortunately, and require that Farmer John milks
 * them in an order that respects N constraints (1≤N≤7). Each constraint is of
 * the form "X must be milked beside Y", stipulating that cow X must appear in
 * the milking order either directly after cow Y or directly before cow Y.
 *
 * Please help Farmer John determine an ordering of his cows that satisfies all
 * of these required constraints. It is guaranteed that an ordering is always
 * possible. If several orderings work, then please output the one that is
 * alphabetically first. That is, the first cow should have the alphabetically
 * lowest name of all possible cows that could appear first in any valid ordering.
 * Among all orderings starting with this same alphabetically-first cow,
 * the second cow should be alphabetically lowest among all possible valid orderings, and so on.
 */

// TODO: Ensure alphabetical ordering

using Constraint = std::pair<std::string, std::string>;
const Constraint EMPTY_CONSTRAINT = {"", ""};

// TODO: Unit tests, maybe?
struct ConstraintSet {
  std::vector<Constraint> constraints;

  [[nodiscard]] bool isSatisfiedBy(const std::vector<std::string> &cowNames) const {
    return std::all_of(constraints.cbegin(), constraints.cend(), [cowNames](auto const &constraint) {
      const auto index0 = std::find(cowNames.cbegin(), cowNames.cend(), constraint.first);
      const auto index1 = std::find(cowNames.cbegin(), cowNames.cend(), constraint.second);

      return std::abs(index0 - index1) == 1;
    });
  }

  [[nodiscard]] std::string getCowThatShowsUpTheMost() const {
    std::map<std::string, uint_fast8_t> cowCount;

    for (const auto &constraint : constraints) {
      cowCount[constraint.first]++;
      cowCount[constraint.second]++;
    }

    auto max = std::max_element(cowCount.cbegin(), cowCount.cend(), [](auto left, auto right) {
      return left.second < right.second;
    });

    return max->first;
  }

  /**
   * Removes a constraint containing the given cow.
   *
   * If there are multiple matching constraints, it will remove exactly one of them, with no guarantees on which one.
   *
   * If there are no matching constraints, it will not remove anything, and will return EMPTY_CONSTRAINT
   */
  Constraint popConstraintWithCow(const std::string &cow) {
    for (auto it = this->constraints.begin(); it != this->constraints.end(); ++it) {
      auto constraint = *it;
      if (cow == constraint.first || cow == constraint.second) {
        this->constraints.erase(it);
        return constraint;
      }
    }

    return EMPTY_CONSTRAINT;
  }
};

std::string getOtherCow(const Constraint &constraint, const std::string &cow) {
  if (constraint.first == cow) {
    return constraint.second;
  } else {
    return constraint.first;
  }
}

ConstraintSet parseConstraints(const std::vector<std::string> &constraints) {
  std::vector<Constraint> parsed;

  std::transform(constraints.cbegin(), constraints.cend(), std::back_inserter(parsed),
                 [](const std::string &constraint) {
                   const auto first = constraint.substr(0, constraint.find_first_of(' '));
                   const auto second = constraint.substr(constraint.find_last_of(' ') + 1);
                   return std::pair{first, second};
                 });

  return ConstraintSet{parsed};
}

ComSci::ConstrainedOrdering::Solution ComSci::ConstrainedOrdering::runBaseline(
    const std::vector<std::string> &cowNames,
    const std::vector<std::string> &constraints) {
  auto sortedCowNames = cowNames;
  const auto constraintSet = parseConstraints(constraints);

  const auto begin = std::begin(sortedCowNames), end = std::end(sortedCowNames);
  std::sort(begin, end);

  do {
    if (constraintSet.isSatisfiedBy(sortedCowNames)) break;
  } while (std::next_permutation(begin, end));

  return Solution{sortedCowNames};
}

// NOLINTNEXTLINE(misc-no-recursion)
std::deque<std::string> runHeuristicWithParsedConstraints(
    const std::deque<std::string> &cowNames,
    ConstraintSet constraints
    ) {
  if (constraints.constraints.empty()) {
    return cowNames;
  }

  auto remainingCowNames = cowNames;

  auto middleCow = constraints.getCowThatShowsUpTheMost();
  auto output = std::deque{middleCow};
  std::erase(remainingCowNames, middleCow);

  auto backConstraint = constraints.popConstraintWithCow(middleCow);
  if (backConstraint != EMPTY_CONSTRAINT) {
    auto backCow = getOtherCow(backConstraint, middleCow);
    output.emplace_back(backCow);
    std::erase(remainingCowNames, backCow);
  }

  auto frontConstraint = constraints.popConstraintWithCow(middleCow);
  if (frontConstraint != EMPTY_CONSTRAINT) {
    auto frontCow = getOtherCow(frontConstraint, middleCow);
    output.emplace_front(frontCow);
    std::erase(remainingCowNames, frontCow);
  }

  auto backCow = output.back();
  auto nextBackConstraint = constraints.popConstraintWithCow(backCow);
  while (nextBackConstraint != EMPTY_CONSTRAINT) {
    backCow = getOtherCow(nextBackConstraint, backCow);
    output.push_back(backCow);
    nextBackConstraint = constraints.popConstraintWithCow(backCow);
  }

  auto frontCow = output.front();
  auto nextFrontConstraint = constraints.popConstraintWithCow(frontCow);
  while (nextFrontConstraint != EMPTY_CONSTRAINT) {
    frontCow = getOtherCow(nextFrontConstraint, frontCow);
    output.push_front(frontCow);
    nextFrontConstraint = constraints.popConstraintWithCow(frontCow);
  }

  auto nextPass = runHeuristicWithParsedConstraints(remainingCowNames, constraints);
  // TODO: Do something smarter here
  for (const auto &cow : nextPass) {
    output.push_back(cow);
  }

  return output;
}

ComSci::ConstrainedOrdering::Solution ComSci::ConstrainedOrdering::runHeuristic(
    const std::vector<std::string> &cowNames,
    const std::vector<std::string> &constraints
    ) {
  auto constraintSet = parseConstraints(constraints);

  // TODO: Do something smarter
  std::deque<std::string> cowNamesDeque;
  for (const auto &cow : cowNames) {
    cowNamesDeque.emplace_back(cow);
  }

  const auto solution = runHeuristicWithParsedConstraints(cowNamesDeque, constraintSet);

  // TODO: Do something smarter
  std::vector<std::string> finalOutput;
  for (const auto &cow : solution) {
    finalOutput.emplace_back(cow);
  }

  return Solution{finalOutput};
}
