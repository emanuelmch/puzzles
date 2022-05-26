/*
 * Copyright (c) 2022 Emanuel Machado da Silva
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

#include "strings.h"

#include "common/assertions.h"

inline char toChar(uint_fast8_t digit, uint_fast8_t base) {
  ensure_m(base == 10U, "haven't implemented other bases yet");
  ensure(digit < base);
  return static_cast<char>(digit + '0');
}

std::string pzl::toString(uint32_t val, uint8_t base) { // NOLINT(readability-magic-numbers)
  uint_fast8_t length = 1U;
  {
    auto value = val;
    while (base <= value) {
      length++;
      value /= base;
    }
  }

  char result[length + 1];
  result[length] = '\0';

  for (auto nextIndex = static_cast<int_fast8_t>(length - 1); nextIndex >= 0; nextIndex--) {
    auto nextDigit = val % base;
    result[nextIndex] = toChar(nextDigit, base);

    val -= nextDigit;
    val /= base;
  }

  return {result};
}
