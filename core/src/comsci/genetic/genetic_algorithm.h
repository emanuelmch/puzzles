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

#include "common/assertions.h" // ensure

#include <memory> // std::shared_ptr

namespace pzl::comsci {

//TODO: Change this to a Concept
template <typename Chromosome>
struct CrossoverStrategy {

  using Iterator = Chromosome *;
  using ConstIterator = Chromosome const *;

  virtual void crossover(ConstIterator parentBegin, ConstIterator parentEnd, Iterator outputBegin,
                         Iterator outputEnd) const = 0;
};

//TODO: Change this to a Concept
template <typename Chromosome>
struct MutationStrategy {

  using Iterator = Chromosome *;

  virtual void mutate(Iterator begin, Iterator end) const = 0;
};

template <typename Chromosome, size_t PopulationSize>
struct GeneticAlgorithm {

  const size_t eliteSize;
  const CrossoverStrategy<Chromosome> &crossoverStrategy;
  const MutationStrategy<Chromosome> &mutationStrategy;

  GeneticAlgorithm(const size_t eliteSize, const CrossoverStrategy<Chromosome> &crossoverStrategy,
                   const MutationStrategy<Chromosome> &mutationStrategy)
      : eliteSize(eliteSize), crossoverStrategy(crossoverStrategy), mutationStrategy(mutationStrategy) {}

  inline std::pair<Chromosome, size_t> runUntilGenerationsSinceLastImprovement(size_t limit) {
    // TODO: Assumes Chromosome{} is a valid and correct constructor
    std::array<Chromosome, PopulationSize> population;
    std::sort(population.rbegin(), population.rend());

    Chromosome solution = population[0];

    size_t generations = 0;
    size_t generationsSinceLastImprovement = 0;

    do {
      std::array<Chromosome, PopulationSize> next = population;
      using diff_type = typename decltype(next)::difference_type;

      auto nonEliteBegin = next.begin();
      std::advance(nonEliteBegin, static_cast<diff_type>(eliteSize));

      // By copying the current population, we already get our elite Chromosomes
      crossoverStrategy.crossover(population.cbegin(), population.cend(), nonEliteBegin, next.end());
      mutationStrategy.mutate(nonEliteBegin, next.end());

      std::sort(next.rbegin(), next.rend());
      if (eliteSize > 0) {
        ensure(next[0].fitness() >= population[0].fitness());
      }
      population = next;

      if (population[0].fitness() > solution.fitness()) {
        solution = population[0];
        generationsSinceLastImprovement = 0;
      }

      ++generations;
      ++generationsSinceLastImprovement;
    } while (generationsSinceLastImprovement < limit);

    return std::make_pair(solution, generations);
  }
};
}
