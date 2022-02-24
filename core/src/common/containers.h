/*
 * Copyright (c) 2021 Emanuel Machado da Silva
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

#include <array>   // std:array
#include <cstddef> // size_t
#include <utility> // std::integer_sequence

namespace pzl {

template <size_t... Indices, typename Gen>
constexpr auto generate_array_from_sequence(std::integer_sequence<size_t, Indices...>, const Gen &generator) {
  using ValueType = decltype(generator(0));
  return std::array<ValueType, sizeof...(Indices)>{generator(Indices)...};
}

template <size_t Size, typename T = size_t, typename Gen>
constexpr auto generate_array(const Gen &generator) {
  auto indexes = std::make_integer_sequence<T, Size>();
  return generate_array_from_sequence(indexes, [&generator](auto) { return generator(); });
}

template <size_t Size, typename T = size_t, typename Gen>
constexpr auto generate_array_indexed(const Gen &generator) {
  auto indexes = std::make_integer_sequence<size_t, Size>();
  return generate_array_from_sequence(indexes, generator);
}

template <size_t Size, typename T = size_t>
constexpr auto generate_array_iota() {
  auto indexes = std::make_integer_sequence<size_t, Size>();
  return generate_array_from_sequence(indexes, [](size_t i) { return (T)i; });
}

}
