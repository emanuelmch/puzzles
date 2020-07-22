/*
 * Copyright (c) 2020 Emanuel Machado da Silva
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

#include "frequency_aware_player.h"

#include "common/collections.h"
#include "hangman/word_repository.h"

#include <iostream>
#include <map>

using namespace Hangman;
using namespace Puzzles;

typedef uint32_t Frequency;
typedef std::map<char, Frequency> FrequencyMap;
typedef std::pair<char, Frequency> FrequencyPair;
typedef std::vector<FrequencyPair> FrequencyVector;

char FrequencyAwarePlayerSession::guess() {
  assert(guesses.empty() == false);

  auto top = guesses.front();
  guesses.pop();
  return top;
}

PlayerSession *FrequencyAwarePlayer::session() {
  if (guessOrder.empty()) init();

  currentSession = FrequencyAwarePlayerSession(guessOrder);
  return &currentSession;
}

static inline FrequencyMap createFrequencyMap() {
  WordRepository repository;
  FrequencyMap frequency;

  for (auto letter = 'A'; letter <= 'Z'; letter++) {
    frequency[letter] = 0;
  }

  for (const auto &word : repository.words()) {
    for (auto letter : word) {
      assert(letter >= 'A' && letter <= 'Z');
      frequency[letter]++;
    }
  }

  return frequency;
}

inline static FrequencyVector convertToPairs(FrequencyMap frequency) {
  FrequencyVector result;

  std::transform(frequency.begin(), frequency.end(), std::back_inserter(result),
                 [](std::pair<char, uint64_t> pair) { return std::pair(pair.first, pair.second); });

  std::sort(result.begin(), result.end(),
            [](FrequencyPair first, FrequencyPair second) { return first.second > second.second; });

  return result;
}

void FrequencyAwarePlayer::init() {
  auto frequency = createFrequencyMap();
  auto pairs = convertToPairs(frequency);

  std::transform(pairs.begin(), pairs.end(), queue_inserter(guessOrder), [](auto value) { return value.first; });
}
