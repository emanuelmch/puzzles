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
#include "common/runners.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <random>

static const uint8_t POPULATION_SIZE = 40;
static const uint8_t ELITE_SIZE = 6;
static const uint8_t MUTATION_CHANCE = 5;
// TODO: These next two values should be randomly calculated
static const uint8_t CROSSOVER_CUTPOINT_LEFT = 1;
static const uint8_t CROSSOVER_CUTPOINT_RIGHT = 3;
static_assert(CROSSOVER_CUTPOINT_LEFT < CROSSOVER_CUTPOINT_RIGHT);
static_assert(CROSSOVER_CUTPOINT_RIGHT < CITY_COUNT);

namespace {

using GeneArray = std::array<uint8_t, CITY_COUNT>;

struct Chromosome {
  GeneArray genes;
  mutable uint8_t _fitness;

  explicit Chromosome(GeneArray genes) : genes(genes), _fitness(0) { ensure(isValid()); }

  [[nodiscard]] inline bool isValid() const {
    constexpr GeneArray base = pzl::generate_array_iota<CITY_COUNT, uint8_t>();

    return std::all_of(base.begin(), base.end(), [&](auto i) { return pzl::ranges::contains(genes, i); });
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

  constexpr bool operator<(const Chromosome &other) const { return this->fitness() > other.fitness(); }
};

inline Chromosome make_chromosome() {
  GeneArray genes = pzl::generate_array_iota<CITY_COUNT, uint8_t>();
  std::shuffle(genes.begin(), genes.end(), std::random_device{});
  return Chromosome(genes);
}
}

template <size_t Count>
inline std::array<Chromosome, Count> selectParents(const std::array<Chromosome, POPULATION_SIZE> &population) {
  std::vector<Chromosome> candidates{population.cbegin(), population.cend()};

  auto next = [&candidates]() {
    ensure(!candidates.empty());
    auto begin = candidates.cbegin();
    auto end = candidates.cend();

    auto sum = std::accumulate(begin, end, 0, [](const auto &sum, const auto &next) { return sum + next.fitness(); });
    auto rnd = std::rand() % sum;
    auto it = begin;

    while (true) {
      ensure(it != end);
      rnd -= it->fitness();
      if (rnd <= 0) {
        auto result = *it;
        candidates.erase(it);
        return result;
      }
    }
  };

  return pzl::generate_array<Count>(next);
}

inline Chromosome crossover(const Chromosome &left, const Chromosome &right) {
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

inline void mutate(Chromosome *begin, Chromosome *end) {
  for (auto it = begin; it != end; ++it) {
    static_assert(MUTATION_CHANCE <= 100);
    if (static_cast<uint8_t>(std::rand() % 100) < MUTATION_CHANCE) {
      auto index1 = static_cast<unsigned long>(std::rand()) % it->genes.size();
      auto index2 = static_cast<unsigned long>(std::rand()) % it->genes.size();
      std::swap(it->genes[index1], it->genes[index2]);

      ensure(it->isValid());
      it->_fitness = 0;
    }
  }
}

ComSci::TravellingSalesman::Solution ComSci::TravellingSalesman::run() {
  auto population = pzl::generate_array<POPULATION_SIZE>(make_chromosome);
  std::sort(population.begin(), population.end());

  Chromosome solution = population[0];

  uint64_t generations = 0;
  uint16_t generationsSinceLastImprovement = 0;

  do {
    std::array<Chromosome, POPULATION_SIZE> next = population;
    // By copying the current population, we already get our elite Chromosomes

    constexpr auto parentCount = POPULATION_SIZE - ELITE_SIZE;
    static_assert(parentCount % 2 == 0);
    auto parents = selectParents<parentCount>(population);
    for (size_t i = 0; i < parentCount; i += 2) {
      next[i + ELITE_SIZE] = crossover(parents[i], parents[i + 1]);
      next[i + ELITE_SIZE + 1] = crossover(parents[i + 1], parents[i]);
    }

    mutate(next.begin(), next.end());

    std::sort(next.begin(), next.end());
    ensure(next[0].fitness() >= population[0].fitness()); // Due to elites, this must be true
    population = next;

    if (population[0].fitness() > solution.fitness()) {
      solution = population[0];
      generationsSinceLastImprovement = 0;
    }

    ++generations;
    ++generationsSinceLastImprovement;
  } while (generationsSinceLastImprovement < 10000);

  std::vector<uint8_t> shortestPath{solution.genes.begin(), solution.genes.end()};
  return {shortestPath, static_cast<uint8_t>(MAX_DISTANCE - solution.fitness())};
}
