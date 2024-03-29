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

#include "travelling_salesman.h"
#include "travelling_salesman_data.h"

#include "common/assertions.h"
#include "common/containers.h"
#include "common/ranges.h"
#include "comsci/genetic/crossover_strategies.h"
#include "comsci/genetic/genetic_algorithm.h"
#include "comsci/genetic/mutation_strategies.h"

#include <algorithm> // std::find_if, std::shuffle, std::swap
#include <array>     // std::array
#include <limits>    // std::numeric_limits
#include <random>    // std::rand

using namespace pzl::comsci;

constexpr auto POPULATION_SIZE = 40;
constexpr auto ELITE_SIZE = 6;
constexpr auto MUTATION_CHANCE = 5;

namespace {

using GeneArray = std::array<uint8_t, CITY_COUNT>;

struct Chromosome {
  GeneArray genes;
  mutable uint8_t _fitness;

  Chromosome() : genes{pzl::generate_array_iota<CITY_COUNT, uint8_t>()}, _fitness{0} {
    std::shuffle(genes.begin(), genes.end(), std::random_device{});
    ensure(isValid());
  }

  explicit Chromosome(GeneArray genes) : genes{genes}, _fitness{0} { ensure(isValid()); }

  [[nodiscard]] constexpr bool isValid() const {
    for (auto i = 0u; i < CITY_COUNT; ++i) {
      if (pzl::ranges::contains(genes, i) == false) {
        return false;
      }
    }
    return true;
  }

  constexpr uint8_t fitness() const {
    if (_fitness == 0) {
      uint8_t distance = 0;

      for (size_t i = 0; i < genes.size() - 1; ++i) {
        auto from = genes[i];
        auto to = genes[i + 1];
        distance += DISTANCE_TABLE[from][to];
      }

      auto last = genes[genes.size() - 1];
      auto first = genes[0];
      distance += DISTANCE_TABLE[last][first];

      _fitness = MAX_DISTANCE - distance;
    }

    ensure(_fitness > 0);
    return _fitness;
  }

  constexpr bool operator<(const Chromosome &other) const { return this->fitness() < other.fitness(); }
};
}

inline Chromosome crossover(const Chromosome &left, const Chromosome &right) {
  // TODO: These next two values should be randomly calculated
  static const uint8_t CROSSOVER_CUTPOINT_LEFT = 1;
  static const uint8_t CROSSOVER_CUTPOINT_RIGHT = 3;
  static_assert(CROSSOVER_CUTPOINT_LEFT < CROSSOVER_CUTPOINT_RIGHT);
  static_assert(CROSSOVER_CUTPOINT_RIGHT < CITY_COUNT);

  GeneArray genes;
  genes.fill(std::numeric_limits<GeneArray::value_type>::max());

  ensure(left.isValid());
  ensure(right.isValid());

  for (auto i = CROSSOVER_CUTPOINT_LEFT; i < CROSSOVER_CUTPOINT_RIGHT; ++i) {
    genes[i] = left.genes[i];
  }

  for (size_t i = 0; i < CITY_COUNT; ++i) {
    if (i >= CROSSOVER_CUTPOINT_LEFT && i < CROSSOVER_CUTPOINT_RIGHT) continue;

    auto it = std::find_if(right.genes.cbegin(), right.genes.cend(),
                           [&genes](const auto &it) { return pzl::ranges::contains(genes, it) == false; });
    genes[i] = *it;
  }

  ensure(pzl::ranges::contains(genes, std::numeric_limits<GeneArray::value_type>::max()) == false);

  return Chromosome(genes);
}

inline void mutate(Chromosome *chromosome) {
  auto index1 = static_cast<size_t>(std::rand()) % CITY_COUNT;
  auto index2 = static_cast<size_t>(std::rand()) % CITY_COUNT;
  std::swap(chromosome->genes[index1], chromosome->genes[index2]);

  ensure(chromosome->isValid());
  // We should always be called on new Chromosomes, due to the way the crossover code works;
  // Otherwise we would have to set it to 0 manually
  ensure(chromosome->_fitness == 0);
}

ComSci::TravellingSalesman::Solution ComSci::TravellingSalesman::run() {
  LambdaCrossoverStrategy<Chromosome> crossoverStrategy{crossover};
  LambdaMutationStrategy<Chromosome, MUTATION_CHANCE> mutationStrategy{mutate};
  auto geneticAlgorithm =
      GeneticAlgorithm<Chromosome, POPULATION_SIZE>{ELITE_SIZE, crossoverStrategy, mutationStrategy};
  auto [solution, generations] = geneticAlgorithm.runUntilGenerationsSinceLastImprovement(100000);

  std::vector<uint8_t> shortestPath{solution.genes.begin(), solution.genes.end()};
  return {shortestPath, static_cast<uint8_t>(MAX_DISTANCE - solution.fitness())};
}
