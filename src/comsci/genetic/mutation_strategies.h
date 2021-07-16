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

#include <cstdint>    // uint8_t
#include <functional> // std::function

// TODO: Create a MutationStrategy concept
template <typename Chromosome, size_t MutationChance>
struct LambdaMutationStrategy {

  const std::function<void(Chromosome *)> mutationFunction;

  explicit LambdaMutationStrategy(const std::function<void(Chromosome *)> &mutationFunction) noexcept
      : mutationFunction(mutationFunction) {}

  template <typename Iter>
  inline void operator()(Iter begin, const Iter &end) const {
    for (auto it = begin; it != end; std::advance(it, 1)) {
      if (static_cast<uint8_t>(std::rand() % 100) < MutationChance) {
        mutationFunction(it);
      }
    }
  }
};
