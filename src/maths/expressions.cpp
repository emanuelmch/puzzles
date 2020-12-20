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

#include "common/assertions.h"

#include <algorithm> // std::remove_if
#include <cmath>     // std::pow
#include <cstdint>   // uint_fast8_t
#include <stack>     // std::stack
#include <vector>    // std::vector

using namespace Maths;

using Puzzles::Numbers::Number;

using std::stack;
using std::string;
using std::vector;

vector<Token> Maths::tokenizeExpression(const string &expression) {
  ensure(expression.find(' ') == expression.npos);
  vector<Token> tokens;

  bool isReadingNumber = false;
  Number currentNumber(0);

  for (const auto token : expression) {
    if (token >= '0' && token <= '9') {
      isReadingNumber = true;
      // TODO: operator*=(int) and operator+=(int)
      currentNumber *= Number(10);
      currentNumber += Number(token - '0');
      continue;
    }

    if (currentNumber != 0) {
      tokens.emplace_back(currentNumber);
      isReadingNumber = false;
      currentNumber = Number(0);
    }

    tokens.emplace_back(token);
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

  ensure_never("Unknown token");
  return 0;
}

void reduceOnce(stack<Number> *numbers, stack<char> *operators) {
  auto next = operators->top();
  operators->pop();

  ensure(std::string("+-*/^").find(next) != std::string::npos);

  ensure(numbers->size() >= 2);
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

inline void reduceToParenthesis(stack<Number> *numbers, stack<char> *operators) {
  ensure(!operators->empty());
  while (operators->top() != '(') {
    reduceOnce(numbers, operators);
    ensure(!operators->empty());
  }
  operators->pop();
}

inline void reduceToPrecedence(stack<Number> *numbers, stack<char> *operators, uint_fast8_t precedence) {
  while (!operators->empty() && getPrecedence(operators->top()) >= precedence) {
    reduceOnce(numbers, operators);
  }
}

inline void replace_all(std::string *expression, const std::string &before, const std::string &after) {
  for (size_t pos = expression->find(before); pos != std::string::npos; pos = expression->find(before, pos)) {
    expression->replace(pos, before.length(), after);
  }
}

Number Maths::evaluateExpression(std::string expression) {
  expression.erase(std::remove_if(expression.begin(), expression.end(), isspace), expression.end());
  replace_all(&expression, "--", "+");
  replace_all(&expression, "++", "+");

  stack<Number> numbers;
  stack<char> operators;
  int parenthesisCount = 0;
  bool isLastTokenAnOperator = false;

  for (const auto &token : tokenizeExpression(expression)) {
    ensure(token != ' ');

    if (token.isNumber) {
      numbers.push(token.asNumber);
    } else if (token == '(') {
      operators.push('(');
      parenthesisCount++;
    } else if (token == ')') {
      ensure(parenthesisCount > 0);
      parenthesisCount--;
      reduceToParenthesis(&numbers, &operators);
    } else if (token == '^') {
      operators.push('^');
    } else if (token == '-' && (numbers.empty() || isLastTokenAnOperator)) {
      numbers.push(Number(-1));
      operators.push('*');
    } else {
      reduceToPrecedence(&numbers, &operators, getPrecedence(token.asOperator));
      operators.push(token.asOperator);
    }

    isLastTokenAnOperator = !token.isNumber && token.asOperator != ')';
  }

  while (!operators.empty()) {
    reduceOnce(&numbers, &operators);
  }

  ensure(numbers.size() == 1);
  return numbers.top();
}
