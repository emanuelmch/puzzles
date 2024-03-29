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

#pragma once

#include "genetic_algorithm.h"

#include "common/assertions.h"

#include <functional> // std::function
#include <numeric> // std::accumulate
#include <vector>  // std::vector

namespace pzl::comsci {

// TODO: Create a CrossoverStrategy concept
template <typename Chromosome>
struct LambdaCrossoverStrategy : public pzl::comsci::CrossoverStrategy<Chromosome> {

  using Iterator = Chromosome *;
  using ConstIterator = Chromosome const *;

  const std::function<Chromosome(const Chromosome &, const Chromosome &)> crossoverFunction;

  explicit LambdaCrossoverStrategy(
      const std::function<Chromosome(const Chromosome &, const Chromosome &)> &crossoverFunction)
      : crossoverFunction(crossoverFunction) {}

  inline std::vector<Chromosome> selectParents(size_t childCount, ConstIterator begin, ConstIterator end) const {
    std::vector<Chromosome> candidates{begin, end};

    auto next = [&candidates]() {
      ensure(!candidates.empty());
      auto begin = candidates.cbegin();
      auto end = candidates.cend();

      auto sum = std::accumulate(begin, end, 0, [](auto sum, const auto &next) { return sum + next.fitness(); });
      auto rnd = std::rand() % sum;
      auto it = begin;

      while (true) {
        ensure(it != end);
        rnd -= it->fitness();
        if (rnd <= 0) {
          auto result = *it;
          candidates.erase(it);
          return result;
        } else {
          ++it;
        }
      }
    };

    std::vector<Chromosome> result;
    result.reserve(childCount);

    for (auto i = 0u; i < childCount; ++i) {
      result.push_back(next());
    }

    return result;
  }

  void crossover(ConstIterator parentBegin, ConstIterator parentEnd, Iterator outputBegin,
                 Iterator outputEnd) const override {
    const auto parentDistance = std::distance(parentBegin, parentEnd);
    const auto outputDistance = std::distance(outputBegin, outputEnd);

    ensure(parentDistance > 0);
    ensure(outputDistance > 0);

    const auto populationSize = static_cast<size_t>(parentDistance);
    const auto childCount = static_cast<size_t>(outputDistance);

    ensure(childCount % 2 == 0);
    ensure(populationSize >= childCount);

    auto parents = selectParents(childCount, parentBegin, parentEnd);
    for (auto i = 0u; i < childCount; i += 2) {
      *outputBegin = crossoverFunction(parents[i], parents[i + 1]);
      ++outputBegin;
      *outputBegin = crossoverFunction(parents[i + 1], parents[i]);
      ++outputBegin;
    }

    ensure(outputBegin == outputEnd);
  }
};

}
