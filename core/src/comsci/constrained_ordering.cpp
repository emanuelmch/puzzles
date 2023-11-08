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

std::vector<Constraint> parseConstraints(const std::vector<std::string> &constraints) {
  std::vector<Constraint> parsedConstraints;

  std::transform(constraints.cbegin(), constraints.cend(), std::back_inserter(parsedConstraints),
                 [](const std::string &constraint) {
                   const auto first = constraint.substr(0, constraint.find_first_of(' '));
                   const auto second = constraint.substr(constraint.find_last_of(' ') + 1);
                   return std::pair{first, second};
                 });

  return parsedConstraints;
}

bool orderSatisfiesConstraints(const std::vector<std::string> &cowNames,
                               const std::vector<Constraint> &constraints) {
  return std::all_of(constraints.cbegin(), constraints.cend(), [cowNames](auto const &constraint) {
    const auto index0 = std::find(cowNames.cbegin(), cowNames.cend(), constraint.first);
    const auto index1 = std::find(cowNames.cbegin(), cowNames.cend(), constraint.second);

    return std::abs(index0 - index1) == 1;
  });
}

ComSci::ConstrainedOrdering::Solution ComSci::ConstrainedOrdering::runBaseline(
    std::vector<std::string> cowNames,
    const std::vector<std::string> &constraints) {
  const auto parsedConstraints = parseConstraints(constraints);

  const auto begin = std::begin(cowNames), end = std::end(cowNames);
  std::sort(begin, end);

  do {
    if (orderSatisfiesConstraints(cowNames, parsedConstraints)) break;
  } while (std::next_permutation(begin, end));

  return Solution{cowNames};
}
