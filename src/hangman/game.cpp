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

#include "game.h"

#include <algorithm>

using namespace Hangman;

inline uint8_t play(PlayerSession *player, std::string word) {
  auto mistakes = 0;

  while (word.empty() == false) {
    auto letter = player->guess();

    if (std::find(word.begin(), word.end(), letter) == word.end()) {
      mistakes++;
    } else {
      word.erase(std::remove(word.begin(), word.end(), letter), word.end());
    }
  }

  return mistakes;
}

GameResults Game::play(Player *player) {
  uint64_t sum = 0;

  std::vector<std::string> words;
  auto completeWords = wordRepository.words();
  for (auto i = 0; i < 10; ++i) {
    words.push_back(completeWords[i]);
  }

  for (const auto &word : words) {
    sum += ::play(player->session(), word);
  }

  return {sum / words.size()};
}
