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

#include "expressions.h"

#include <cassert>
#include <cstdint>
#include <stack>

using namespace Maths;

using std::stack;

const uint_fast8_t UINT_FAST8_MIN = 0;

void reduce(stack<int> *numbers, stack<char> *operators, uint_fast8_t precedence);

inline uint_fast8_t getPrecedence(char operation) {
  if (operation == '+' || operation == '-') return 1;

  assert(!"Unknown token");
  return 0;
}

int Maths::evaluateExpression(const std::string &expression) {
  stack<int> numbers;
  stack<char> operators;

  for (auto token : expression) {
    if (token == ' ') continue;

    if (token >= '0' && token <= '9') {
      numbers.push(token - '0');
    } else if (token == '+' || token == '-') {
      reduce(&numbers, &operators, getPrecedence(token));
      operators.push(token);
    } else
      assert(!"Unknown token");
  }
  reduce(&numbers, &operators, UINT_FAST8_MIN);

  assert(numbers.size() == 1);

  return numbers.top();
}

void reduce(stack<int> *numbers, stack<char> *operators, uint_fast8_t precedence) {
  while (!operators->empty()) {
    auto next = operators->top();
    if (getPrecedence(next) < precedence) return;
    operators->pop();

    assert(next == '+' || next == '-');

    assert(numbers->size() >= 2);
    auto right = numbers->top();
    numbers->pop();
    auto left = numbers->top();
    numbers->pop();

    if (next == '+') {
      numbers->push(left + right);
    } else if (next == '-') {
      numbers->push(left - right);
    }
  }
}