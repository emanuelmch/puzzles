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

#include <cstdint>    // uint8_t
#include <functional> // std::function

namespace pzl::comsci {

// TODO: Create a MutationStrategy concept
template <typename Chromosome, uint8_t MutationChance>
struct LambdaMutationStrategy : public MutationStrategy<Chromosome> {

  using Iterator = Chromosome *;

  const std::function<void(Chromosome *)> mutationFunction;

  explicit LambdaMutationStrategy(const std::function<void(Chromosome *)> &mutationFunction)
      : mutationFunction(mutationFunction) {}

  void mutate(Iterator begin, Iterator end) const override {
    for (auto it = begin; it != end; ++it) {
      if (std::rand() % 100 < MutationChance) {
        mutationFunction(it);
      }
    }
  }
};
}
