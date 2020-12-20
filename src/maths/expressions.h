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

#pragma once

#include "common/numbers.h"

#include <string>
#include <utility>
#include <vector>

namespace Maths {

struct Token {
  bool isNumber;
  char asOperator;
  Puzzles::Numbers::Number asNumber;

  explicit Token(Puzzles::Numbers::Number number) : isNumber(true), asOperator(0), asNumber(std::move(number)) {}

  explicit Token(char anOperator) : isNumber(false), asOperator(anOperator), asNumber(0) {}

  inline bool operator==(const char anOperator) const { return !isNumber && asOperator == anOperator; }
  inline bool operator!=(const char anOperator) const { return isNumber || asOperator != anOperator; }

  inline bool operator==(const Token &o) const {
    if (isNumber != o.isNumber) return false;
    if (isNumber) {
      return asNumber == o.asNumber;
    } else {
      return asOperator == o.asOperator;
    }
  }

private:
  inline Token(bool isNumber, char asOperator, Puzzles::Numbers::Number asNumber)
      : isNumber(isNumber), asOperator(asOperator), asNumber(std::move(asNumber)) {}
};

std::vector<Token> tokenizeExpression(const std::string &);

Puzzles::Numbers::Number evaluateExpression(std::string);
}

namespace std { // NOLINT(cert-dcl58-cpp)

inline string to_string(const Maths::Token &token) {
  if (token.isNumber) {
    return std::to_string(token.asNumber);
  } else {
    return std::string(1, token.asOperator);
  }
}

inline string to_string(const vector<Maths::Token> &tokens) {
  string result = "{";
  for (const auto &token : tokens) {
    result += to_string(token) + ",";
  }
  return result + "}";
}

}
