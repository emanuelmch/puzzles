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

#include "ex8_atoi.h"

#include <limits>

using namespace Puzzles::LeetCode;

using std::string;
using std::string_view;

constexpr inline int constCountDigits(int i) {
  if (i == 0) return 0;

  int count = 1;
  while (i > 10) {
    count++;
    i = i / 10;
  }

  return count;
}

int Puzzles::LeetCode::countDigits(int i) {
  return constCountDigits(i);
}

inline size_t countLeftWhitespace(const string_view &str) {
  auto i = 0;
  while (str[i] == ' ') {
    i++;
  }
  return i;
}

inline int overflow(const char &c) {
  if (c == '-') {
    return std::numeric_limits<int>::min();
  } else {
    return std::numeric_limits<int>::max();
  }
}

int Puzzles::LeetCode::myAtoi_firstAttempt(const string &str) {
  constexpr auto MAX = std::numeric_limits<int>::max();
  constexpr auto MIN = std::numeric_limits<int>::min();

  long result = 0;

  const auto start = str.begin() + countLeftWhitespace(str);
  for (auto it = start; it < str.end(); ++it) {
    auto c = *it;

    if (it == start && (c == '+' || c == '-')) continue;

    if (c < '0' || c > '9') break;

    result = (result * 10) + (c - '0');
    if (result > std::numeric_limits<int>::max()) break;
  }

  if (*start == '-') {
    result *= -1;
  }

  if (result > MAX) {
    return MAX;
  } else if (result < MIN) {
    return MIN;
  } else {
    return int(result);
  }
}

int Puzzles::LeetCode::myAtoi_refined(const string &str) {
  constexpr auto MAX = std::numeric_limits<int>::max();
  int result = 0;

  const auto start = str.begin() + countLeftWhitespace(str);

  for (auto it = start; it < str.end(); ++it) {
    auto c = *it;

    if (it == start && (c == '+' || c == '-')) continue;

    if (c < '0' || c > '9') break;

    // AWFUL WORKAROUND
    if (result > (MAX / 10)) return overflow(*start);

    const auto diff = 9 * result + (c - '0');

    if (diff > MAX - result) return overflow(*start);

    result += diff;
  }

  if (*start == '-') {
    return result * -1;
  } else {
    return result;
  }
}

inline int readPositiveNumber(string::const_iterator start, string::const_iterator end) {
  constexpr auto MAX = std::numeric_limits<int>::max();
  constexpr auto MAX_DIGITS = constCountDigits(MAX);

  auto len = end - start;
  if (len > MAX_DIGITS) {
    return MAX;
  } else if (len == MAX_DIGITS) {
    int result = 0;

    auto last = end - 1;
    for (auto it = start; it < end; ++it) {
      auto c = *it;

      if (it != last) {
        result = result * 10 + (c - '0');
      } else {
        // AWFUL WORKAROUND
        if (result > (MAX / 10)) return MAX;

        const auto diff = 9 * result + (c - '0');
        if (diff > MAX - result) return MAX;

        return result + diff;
      }
    }
  } else { // len < MAX_DIGITS
    int result = 0;

    for (auto it = start; it < end; ++it) {
      auto c = *it;
      result = result * 10 + (c - '0');
    }

    return result;
  }
}

inline int readNegativeNumber(string::const_iterator start, string::const_iterator end) {
  constexpr auto MIN = std::numeric_limits<int>::min();
  int result = 0;

  for (auto it = start; it < end; ++it) {
    auto c = *it;

    // AWFUL WORKAROUND
    if (result < (MIN / 10)) return MIN;

    const auto diff = 9 * result - (c - '0');

    if (diff < MIN - result) return MIN;

    result += diff;
  }

  return result;
}

int Puzzles::LeetCode::myAtoi_cretino(const string &str) {
  auto start = str.begin();
  while (*start == ' ')
    ++start;

  bool isNegative = false;

  if (*start == '-') {
    isNegative = true;
    start++;
  } else if (*start == '+') {
    start++;
  }

  while (*start == '0')
    ++start;

  auto end = start;
  while (*end >= '0' && *end <= '9' && end != str.end()) end++;

  if (isNegative) {
    return readNegativeNumber(start, end);
  } else {
    return readPositiveNumber(start, end);
  }
}
