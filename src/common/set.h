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

#include <set>

namespace Puzzles {

#ifdef HAS_STD_SET_CONTAINS
// We have all we need from std::set
template <typename Key, typename Compare = std::less<Key>, typename Alloc = std::allocator<Key>>
using set = std::set<Key, Compare, Alloc>;
#else
// std::set is incomplete, we need more (in this case, just std::set::contains)
template <typename Key, typename Compare = std::less<Key>, typename Alloc = std::allocator<Key>>
struct set : public std::set<Key, Compare, Alloc> {
  set(std::initializer_list<Key> init) : std::set<Key, Compare, Alloc>(init) {}

  inline bool contains(Key item) { return this->find(item) != this->end(); }
};
#endif

};
