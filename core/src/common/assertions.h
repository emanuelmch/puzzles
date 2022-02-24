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

#define UNUSED(x) ((void)x)

#if defined(NDEBUG)

#define ensure(condition) (static_cast<void>(0))
#define ensure_m(condition, message) (static_cast<void>(0))
#define ensure_never(message) (static_cast<void>(0))

#else // defined(NDEBUG)

#include <sstream>   // std::stringstream
#include <stdexcept> // std::logic_error
#include <string>    // std::string

#define ensure(condition)                                                                                              \
  (static_cast<bool>(condition) ? static_cast<void>(0)                                                                 \
                                : throw std::logic_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) +      \
                                                         ": Assertion failed: " + #condition))

#define ensure_m(condition, message)                                                                                   \
  (static_cast<bool>(condition)                                                                                        \
       ? static_cast<void>(0)                                                                                          \
       : throw std::logic_error(((std::stringstream &)(std::stringstream().flush()                                     \
                                                       << std::string(__FILE__) << ":" << std::to_string(__LINE__)     \
                                                       << ": Assertion failed: " << #condition << ", " << message))    \
                                    .str()))

#define ensure_never(message)                                                                                          \
  (throw std::logic_error(                                                                                             \
      ((std::stringstream &)(std::stringstream().flush() << std::string(__FILE__) << ":" << std::to_string(__LINE__)   \
                                                         << ": Reached code that should be unreachable: " << message)) \
          .str()))

#endif // defined(NDEBUG)
