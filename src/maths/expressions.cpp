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
#include <cmath>
#include <cstdint>
#include <stack>

using namespace Maths;

using std::stack;
using std::string;
using std::vector;

vector<Token> Maths::tokenizeExpression(const string &expression) {
  vector<Token> tokens;

  bool isReadingNumber = false;
  int currentNumber = 0;

  for (auto token : expression) {
    if (token >= '0' && token <= '9') {
      isReadingNumber = true;
      currentNumber *= 10;
      currentNumber += token - '0';
      continue;
    }

    if (currentNumber != 0) {
      tokens.emplace_back(currentNumber);
      isReadingNumber = false;
      currentNumber = 0;
    }

    if (token != ' ') {
      tokens.emplace_back(token);
    }
  }

  if (isReadingNumber) {
    tokens.emplace_back(currentNumber);
  }

  return tokens;
}

inline uint_fast8_t getPrecedence(char operation) {
  if (operation == '(') return 0;
  if (operation == '+' || operation == '-') return 1;
  if (operation == '*' || operation == '/') return 2;
  if (operation == '^') return 3;

  assert(!"Unknown token");
  return 0;
}

void reduceOnce(stack<int> *numbers, stack<char> *operators) {
  auto next = operators->top();
  operators->pop();

  assert(next == '+' || next == '-' || next == '*' || next == '/' || next == '^');

  assert(numbers->size() >= 2);
  auto right = numbers->top();
  numbers->pop();
  auto left = numbers->top();
  numbers->pop();

  if (next == '+') {
    numbers->push(left + right);
  } else if (next == '-') {
    numbers->push(left - right);
  } else if (next == '*') {
    numbers->push(left * right);
  } else if (next == '/') {
    numbers->push(left / right);
  } else if (next == '^') {
    numbers->push(std::pow(left, right));
  }
}

inline void reduceToParenthesis(stack<int> *numbers, stack<char> *operators) {
  assert(!operators->empty());
  while (operators->top() != '(') {
    reduceOnce(numbers, operators);
    assert(!operators->empty());
  }
  operators->pop();
}

inline void reduceToPrecedence(stack<int> *numbers, stack<char> *operators, uint_fast8_t precedence) {
  while (!operators->empty() && getPrecedence(operators->top()) >= precedence) {
    reduceOnce(numbers, operators);
  }
}

int Maths::evaluateExpression(const std::string &expression) {
  stack<int> numbers;
  stack<char> operators;
  int parenthesisCount = 0;

  for (auto token : tokenizeExpression(expression)) {
    if (token == ' ') continue;

    if (token.isNumber) {
      numbers.push(token.value.asNumber);
    } else if (token == '(') {
      operators.push('(');
      parenthesisCount++;
    } else if (token == ')') {
      assert(parenthesisCount > 0);
      parenthesisCount--;
      reduceToParenthesis(&numbers, &operators);
    } else {
      reduceToPrecedence(&numbers, &operators, getPrecedence(token.value.asOperator));
      operators.push(token.value.asOperator);
    }
  }

  while (!operators.empty()) {
    reduceOnce(&numbers, &operators);
  }

  assert(numbers.size() == 1);
  return numbers.top();
}
