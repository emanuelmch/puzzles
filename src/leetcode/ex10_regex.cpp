/*
 * Copyright (c) 2019 Emanuel Machado da Silva
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

#include "ex10_regex.h"

#include <iostream>

using std::string;
// FIXME: Must find a better name than "strit"
using strit = std::string::const_iterator;

static bool matches(strit text, const strit &textEnd, strit pattern, const strit &patternEnd) {
  while (pattern != patternEnd && text != textEnd && *(pattern + 1) != '*') {
    auto symbol = *pattern;
    if (symbol == '.' || symbol == *text) {
      pattern++;
      text++;
    } else {
      return false;
    }
  }

  if (pattern == patternEnd) {
    return text == textEnd;
  }

  if (text == textEnd && *(pattern + 1) != '*') {
    return false;
  }

  const auto patternNext = pattern + 2;
  if (matches(text, textEnd, patternNext, patternEnd)) {
    return true;
  }

  const auto symbol = *pattern;
  if (symbol == '.') {
    for (auto it = text; it <= textEnd; it++) {
      if (matches(it, textEnd, patternNext, patternEnd)) {
        return true;
      }
    }
  } else {
    do {
      if (symbol != *text) return false;
      if (matches(++text, textEnd, patternNext, patternEnd)) {
        return true;
      }
    } while (text != textEnd);
  }

  return false;
}

bool Puzzles::LeetCode::isMatch(const string &s, const string &p) {
  return matches(s.begin(), s.end(), p.begin(), p.end());
}
